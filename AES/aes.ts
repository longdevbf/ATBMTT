// aes.ts
import { sbox, Rcon } from "./aes_tables";
import { bytesToHex } from "./utils";

export class AES {
  private state = new Uint8Array(16); // stored column-major as state[row + 4*col]
  private roundKeys: Uint8Array[] = []; // 11 round keys, each 16 bytes
  private key = new Uint8Array(16);

  constructor(keyBytes: Uint8Array) {
    if (keyBytes.length !== 16) throw new Error("Key must be 16 bytes");
    this.key.set(keyBytes);
    this.keyExpansion();
  }

  // Galois Field multiply (GF(2^8))
  private gmul(a: number, b: number): number {
    let p = 0;
    for (let i = 0; i < 8; i++) {
      if (b & 1) p ^= a;
      const hi = a & 0x80;
      a = (a << 1) & 0xFF;
      if (hi) a ^= 0x1B;
      b >>= 1;
    }
    return p;
  }

  private printState(label: string) {
    // print as 4 rows showing state[row][col]
    console.log(label + ":");
    for (let r = 0; r < 4; r++) {
      const row: string[] = [];
      for (let c = 0; c < 4; c++) {
        const val = this.state[r + 4 * c];
        row.push(val.toString(16).padStart(2, "0").toUpperCase());
      }
      console.log(row.join(" "));
    }
    console.log("");
  }

  private subBytes() {
    for (let i = 0; i < 16; i++) this.state[i] = sbox[this.state[i]];
  }

  private shiftRows() {
    // row r is shifted left by r
    const tmp = new Uint8Array(16);
    for (let r = 0; r < 4; r++) {
      for (let c = 0; c < 4; c++) {
        tmp[r + 4 * c] = this.state[r + 4 * ((c + r) % 4)];
      }
    }
    this.state.set(tmp);
  }

  private mixColumns() {
    for (let c = 0; c < 4; c++) {
      const i = 4 * c;
      const a0 = this.state[i + 0], a1 = this.state[i + 1], a2 = this.state[i + 2], a3 = this.state[i + 3];
      const b0 = this.gmul(0x02, a0) ^ this.gmul(0x03, a1) ^ a2 ^ a3;
      const b1 = a0 ^ this.gmul(0x02, a1) ^ this.gmul(0x03, a2) ^ a3;
      const b2 = a0 ^ a1 ^ this.gmul(0x02, a2) ^ this.gmul(0x03, a3);
      const b3 = this.gmul(0x03, a0) ^ a1 ^ a2 ^ this.gmul(0x02, a3);
      this.state[i + 0] = b0 & 0xFF;
      this.state[i + 1] = b1 & 0xFF;
      this.state[i + 2] = b2 & 0xFF;
      this.state[i + 3] = b3 & 0xFF;
    }
  }

  private addRoundKey(round: number) {
    const rk = this.roundKeys[round];
    for (let i = 0; i < 16; i++) this.state[i] ^= rk[i];
    this.printState(`After AddRoundKey (${round})`);
  }

  private keyExpansion() {
    // roundKeys as 11 * 16 bytes
    this.roundKeys = [];
    this.roundKeys[0] = new Uint8Array(16);
    for (let i = 0; i < 16; i++) this.roundKeys[0][i] = this.key[i];
    for (let round = 1; round <= 10; round++) {
      const prev = this.roundKeys[round - 1];
      const t = new Uint8Array(4);
      t[0] = prev[12]; t[1] = prev[13]; t[2] = prev[14]; t[3] = prev[15];
      // RotWord
      const tmp = t[0]; t[0]=t[1]; t[1]=t[2]; t[2]=t[3]; t[3]=tmp;
      // SubWord
      for (let i = 0; i < 4; i++) t[i] = sbox[t[i]];
      t[0] ^= Rcon[round];
      const rk = new Uint8Array(16);
      for (let c = 0; c < 4; c++) {
        for (let r = 0; r < 4; r++) {
          const idx = r + 4 * c;
          if (c === 0) rk[idx] = prev[idx] ^ t[r];
          else rk[idx] = prev[idx] ^ rk[r + 4 * (c - 1)];
        }
      }
      this.roundKeys[round] = rk;
    }
  }

  // debug flag: if true, prints states each step
  encrypt(plaintextBytes: Uint8Array, debug = true): Uint8Array {
    if (plaintextBytes.length !== 16) throw new Error("Plaintext must be 16 bytes");
    // load into state column-major: state[row + 4*col] = plaintext[i]
    for (let i = 0; i < 16; i++) this.state[i] = plaintextBytes[i];

    if (debug) {
      console.log("\n===== START AES ENCRYPTION =====");
      this.printState("Initial State");
    }

    this.addRoundKey(0);

    for (let round = 1; round < 10; round++) {
      if (debug) console.log(`\n--- Round ${round} ---`);
      this.subBytes(); if (debug) this.printState("After SubBytes");
      this.shiftRows(); if (debug) this.printState("After ShiftRows");
      this.mixColumns(); if (debug) this.printState("After MixColumns");
      this.addRoundKey(round);
    }

    if (debug) console.log("\n--- Final Round (10) ---");
    this.subBytes(); if (debug) this.printState("After SubBytes");
    this.shiftRows(); if (debug) this.printState("After ShiftRows");
    this.addRoundKey(10);

    const out = new Uint8Array(16);
    for (let i = 0; i < 16; i++) out[i] = this.state[i];
    if (debug) {
      console.log("\n===== ENCRYPTION COMPLETE =====");
      console.log("Ciphertext (HEX):", bytesToHex(out));
    }
    return out;
  }
}
