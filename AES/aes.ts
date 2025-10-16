import { sbox } from "./aes_tables";
import { Byte, G, mul02, mul03 } from "./utils";

export function keyExpansion(key: Byte[], w: number[][]) {
  for (let i = 0; i < 4; i++) {
    for (let j = 0; j < 4; j++) {
      w[i][j] = key[4 * i + j];
    }
  }
  const temp = [0,0,0,0];
  for (let i = 4; i < 44; i++) {
    for (let j = 0; j < 4; j++) temp[j] = w[i-1][j];
    if (i % 4 === 0) G(temp, Math.floor(i/4));
    for (let j = 0; j < 4; j++) w[i][j] = w[i-4][j] ^ temp[j];
  }
}

export function printStateMatrix(state: Byte[], round: number) {
  console.log(`Round ${round} state (4x4):`);
  for (let r = 0; r < 4; r++) {
    let line = "";
    for (let c = 0; c < 4; c++) {
      const v = state[r + 4 * c] & 0xFF;
      line += v.toString(16).padStart(2, "0").toUpperCase() + " ";
    }
    console.log(line.trim());
  }
  console.log("");
}

export function addRoundKey(state: Byte[], w: number[][], round: number) {
  for (let i = 0; i < 16; i++) {
    state[i] ^= w[round * 4 + Math.floor(i/4)][i % 4];
  }
}

export function subBytes(state: Byte[]) {
  for (let i = 0; i < 16; i++) state[i] = sbox[state[i]];
}

export function shiftRows(state: Byte[]) {
  const t = new Array(4).fill(0);
  for (let r = 1; r < 4; r++) {
    for (let c = 0; c < 4; c++) t[c] = state[r + 4 * c];
    for (let c = 0; c < 4; c++) state[r + 4 * c] = t[(c + r) % 4];
  }
}

export function mixColumns(state: Byte[]) {
  for (let c = 0; c < 4; c++) {
    const a0 = state[0 + 4 * c];
    const a1 = state[1 + 4 * c];
    const a2 = state[2 + 4 * c];
    const a3 = state[3 + 4 * c];
    const r0 = (mul02(a0) ^ mul03(a1) ^ a2 ^ a3) & 0xFF;
    const r1 = (a0 ^ mul02(a1) ^ mul03(a2) ^ a3) & 0xFF;
    const r2 = (a0 ^ a1 ^ mul02(a2) ^ mul03(a3)) & 0xFF;
    const r3 = (mul03(a0) ^ a1 ^ a2 ^ mul02(a3)) & 0xFF;
    state[0 + 4 * c] = r0;
    state[1 + 4 * c] = r1;
    state[2 + 4 * c] = r2;
    state[3 + 4 * c] = r3;
  }
}
