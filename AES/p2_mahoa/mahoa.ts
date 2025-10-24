import * as readline from "readline";
import { sbox, Rcon } from "../aes_tables";
import { hexToByte, mul02, mul03 } from "../utils";

async function question(prompt: string): Promise<string> {
  const rl = readline.createInterface({ input: process.stdin, output: process.stdout });
  return new Promise(resolve => rl.question(prompt, ans => { rl.close(); resolve(ans.trim()); }));
}

function stateToHex(state: number[]): string {
  return state.map(b => b.toString(16).padStart(2, '0').toUpperCase()).join('');
}

function printState(state: number[], label: string) {
  console.log(`${label}:`);
  for (let r = 0; r < 4; r++) {
    let line = "";
    for (let c = 0; c < 4; c++) {
      const v = state[r + 4 * c] & 0xFF;
      line += v.toString(16).padStart(2, "0").toUpperCase() + " ";
    }
    console.log("  " + line.trim());
  }
  console.log(`  Hex: ${stateToHex(state)}`);
}

// Sinh khóa (tương tự keygen.ts nhưng không in ra)
function keyExpansion(key: number[]): number[][] {
  const w: number[][] = [];
  
  for (let i = 0; i < 4; i++) {
    w[i] = [key[4*i], key[4*i+1], key[4*i+2], key[4*i+3]];
  }
  
  const temp = [0, 0, 0, 0];
  for (let i = 4; i < 44; i++) {
    for (let j = 0; j < 4; j++) temp[j] = w[i-1][j];
    
    if (i % 4 === 0) {
      // RotWord
      const t = temp[0];
      temp[0] = temp[1]; temp[1] = temp[2]; temp[2] = temp[3]; temp[3] = t;
      // SubWord
      for (let j = 0; j < 4; j++) temp[j] = sbox[temp[j]];
      // XOR Rcon
      temp[0] ^= Rcon[Math.floor(i / 4)];
    }
    
    w[i] = [];
    for (let j = 0; j < 4; j++) w[i][j] = w[i-4][j] ^ temp[j];
  }
  
  return w;
}

function addRoundKey(state: number[], w: number[][], round: number) {
  for (let i = 0; i < 16; i++) {
    state[i] ^= w[round * 4 + Math.floor(i/4)][i % 4];
  }
}

function subBytes(state: number[]) {
  for (let i = 0; i < 16; i++) state[i] = sbox[state[i]];
}

function shiftRows(state: number[]) {
  const t = new Array(4).fill(0);
  for (let r = 1; r < 4; r++) {
    for (let c = 0; c < 4; c++) t[c] = state[r + 4 * c];
    for (let c = 0; c < 4; c++) state[r + 4 * c] = t[(c + r) % 4];
  }
}

function mixColumns(state: number[]) {
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

(async () => {
  try {
    console.log("========== PHẦN 2: MÃ HÓA AES ==========\n");
    
    const messageInput = await question("Nhập message M (32 ký tự hex): ");
    const keyInput = await question("Nhập khóa K (32 ký tự hex): ");
    
    if (messageInput.length !== 32 || keyInput.length !== 32) {
      console.error("Lỗi: phải nhập đúng 32 ký tự hex cho message và key");
      process.exit(1);
    }

    console.log(`\nInput: M = ${messageInput}`);
    console.log(`Input: K = ${keyInput}\n`);

    // Chuyển sang byte array
    const message: number[] = [];
    const key: number[] = [];
    for (let i = 0; i < 16; i++) {
      message.push(hexToByte(messageInput.substr(i * 2, 2)));
      key.push(hexToByte(keyInput.substr(i * 2, 2)));
    }

    // Sinh khóa
    const w = keyExpansion(key);

    // State ban đầu
    const state = [...message];

    // ========== BÀI 6: AddRoundKey ban đầu ==========
    console.log("========== BÀI 6: TÍNH KẾT QUẢ AddRoundKey ==========");
    console.log(`Input: M = ${messageInput}`);
    console.log(`Input: K = ${keyInput}`);
    addRoundKey(state, w, 0);
    console.log("Output:");
    printState(state, "state = AddRoundKey(M, K)");
    console.log();

    // ========== 9 VÒNG LẶP ĐẦU TIÊN ==========
    for (let round = 1; round <= 9; round++) {
      console.log(`========== VÒNG LẶP THỨ ${round} ==========\n`);
      
      const inputState = stateToHex(state);

      // BÀI 7: SubBytes
      console.log("--- Bài 7: SubBytes ---");
      console.log(`Input: state = ${inputState}`);
      subBytes(state);
      console.log("Output:");
      printState(state, "state = SubBytes(state)");
      console.log();

      // BÀI 8: ShiftRows
      console.log("--- Bài 8: ShiftRows ---");
      console.log(`Input: state = ${stateToHex(state)}`);
      shiftRows(state);
      console.log("Output:");
      printState(state, "state = ShiftRows(state)");
      console.log();

      // BÀI 9: MixColumns
      console.log("--- Bài 9: MixColumns ---");
      console.log(`Input: state = ${stateToHex(state)}`);
      mixColumns(state);
      console.log("Output:");
      printState(state, "state = MixColumns(state)");
      console.log();

      // BÀI 10: AddRoundKey
      console.log("--- Bài 10: AddRoundKey ---");
      console.log(`Input: state = ${stateToHex(state)}`);
      const Ki = w[round * 4].concat(w[round * 4 + 1], w[round * 4 + 2], w[round * 4 + 3]);
      console.log(`Input: K${round} = ${Ki.map(b => b.toString(16).padStart(2, '0').toUpperCase()).join('')}`);
      addRoundKey(state, w, round);
      console.log("Output:");
      printState(state, `state = AddRoundKey(state, K${round})`);
      console.log();
    }

    // ========== VÒNG LẶP THỨ 10 (CUỐI) ==========
    console.log("========== VÒNG LẶP THỨ 10 (VÒNG CUỐI) ==========\n");
    
    console.log("--- Bài 11: Vòng lặp cuối (SubBytes, ShiftRows, AddRoundKey) ---");
    console.log(`Input: state = ${stateToHex(state)}`);
    
    // SubBytes
    subBytes(state);
    console.log("\nSau SubBytes:");
    printState(state, "state");
    
    // ShiftRows
    shiftRows(state);
    console.log("\nSau ShiftRows:");
    printState(state, "state");
    
    // AddRoundKey với K10
    const K10 = w[40].concat(w[41], w[42], w[43]);
    console.log(`\nInput: K10 = ${K10.map(b => b.toString(16).padStart(2, '0').toUpperCase()).join('')}`);
    addRoundKey(state, w, 10);
    
    console.log("\n========== KẾT QUẢ CUỐI CÙNG ==========");
    printState(state, "C = Ciphertext");
    console.log(`\n>>> CIPHERTEXT: ${stateToHex(state)}`);

  } catch (e) {
    console.error("Error:", e);
    process.exit(1);
  }
})();