import * as readline from "readline";
import { sbox, Rcon } from "../aes_tables";
import { hexToByte, bytesToHexString } from "../utils";

async function question(prompt: string): Promise<string> {
  const rl = readline.createInterface({ input: process.stdin, output: process.stdout });
  return new Promise(resolve => rl.question(prompt, ans => { rl.close(); resolve(ans.trim()); }));
}

function wordToHex(w: number[]): string {
  return w.map(b => b.toString(16).padStart(2, '0').toUpperCase()).join('');
}

function rotWord(w: number[]): number[] {
  return [w[1], w[2], w[3], w[0]];
}

function subWord(w: number[]): number[] {
  return w.map(b => sbox[b]);
}

function xorRcon(w: number[], round: number): number[] {
  const result = [...w];
  result[0] ^= Rcon[round];
  return result;
}

function xorWords(w1: number[], w2: number[]): number[] {
  return w1.map((b, i) => b ^ w2[i]);
}

(async () => {
  try {
    console.log("========== PHẦN 1: SINH 10 KHÓA Ki TỪ KHÓA K ==========\n");
    
    const keyInput = await question("Nhập khóa K (32 ký tự hex): ");
    
    if (keyInput.length !== 32) {
      console.error("Lỗi: phải nhập đúng 32 ký tự hex cho key");
      process.exit(1);
    }

    console.log(`\nInput: K = ${keyInput}\n`);

    // Chuyển key thành mảng byte
    const key: number[] = [];
    for (let i = 0; i < 16; i++) {
      key.push(hexToByte(keyInput.substr(i * 2, 2)));
    }

    // Khởi tạo mảng words
    const w: number[][] = [];

    // ========== BÀI 1: Chia khóa K thành 4 word ==========
    console.log("========== BÀI 1: CHIA KHÓA K THÀNH 4 WORD (32 BIT) ==========");
    console.log(`Input: K = ${keyInput}`);
    
    for (let i = 0; i < 4; i++) {
      w[i] = [key[4*i], key[4*i+1], key[4*i+2], key[4*i+3]];
      console.log(`Output: w${i} = ${wordToHex(w[i])}`);
    }
    console.log();

    // ========== SINH 10 KHÓA K1 đến K10 ==========
    for (let round = 1; round <= 10; round++) {
      console.log(`========== SINH KHÓA K${round} ==========`);
      
      const prevW3 = w[w.length - 1];
      
      // BÀI 2: RotWord
      console.log(`\n--- Bài 2: Dịch vòng trái 1 byte (RotWord) ---`);
      console.log(`Input: w${w.length - 1} = ${wordToHex(prevW3)}`);
      const rw = rotWord(prevW3);
      console.log(`Output: rw = RotWord(w${w.length - 1}) = ${wordToHex(rw)}`);

      // BÀI 3: SubWord
      console.log(`\n--- Bài 3: Thay thế từng byte bằng S-box (SubWord) ---`);
      console.log(`Input: rw = ${wordToHex(rw)}`);
      const sw = subWord(rw);
      console.log(`Output: sw = SubWord(rw) = ${wordToHex(sw)}`);

      // BÀI 4: XOR với Rcon
      console.log(`\n--- Bài 4: XOR với Rcon[${round}] ---`);
      console.log(`Input: sw = ${wordToHex(sw)}, Rcon[${round}] = ${Rcon[round].toString(16).padStart(2, '0').toUpperCase()}`);
      const xcsw = xorRcon(sw, round);
      console.log(`Output: xcsw = XorRcon(sw, Rcon[${round}]) = ${wordToHex(xcsw)}`);

      // BÀI 5: Tính w4, w5, w6, w7 (hoặc wi, wi+1, wi+2, wi+3)
      console.log(`\n--- Bài 5: Tính khóa K${round} = (w${w.length}, w${w.length+1}, w${w.length+2}, w${w.length+3}) ---`);
      const baseIdx = w.length - 4;
      console.log(`Input: xcsw = ${wordToHex(xcsw)}`);
      console.log(`       w${baseIdx} = ${wordToHex(w[baseIdx])}`);
      console.log(`       w${baseIdx+1} = ${wordToHex(w[baseIdx+1])}`);
      console.log(`       w${baseIdx+2} = ${wordToHex(w[baseIdx+2])}`);
      console.log(`       w${baseIdx+3} = ${wordToHex(w[baseIdx+3])}`);
      
      const w4 = xorWords(xcsw, w[baseIdx]);
      const w5 = xorWords(w4, w[baseIdx + 1]);
      const w6 = xorWords(w5, w[baseIdx + 2]);
      const w7 = xorWords(w6, w[baseIdx + 3]);
      
      w.push(w4, w5, w6, w7);
      
      console.log(`Output: w${w.length - 4} = XORbit(xcsw, w${baseIdx}) = ${wordToHex(w4)}`);
      console.log(`        w${w.length - 3} = XORbit(w${w.length - 4}, w${baseIdx+1}) = ${wordToHex(w5)}`);
      console.log(`        w${w.length - 2} = XORbit(w${w.length - 3}, w${baseIdx+2}) = ${wordToHex(w6)}`);
      console.log(`        w${w.length - 1} = XORbit(w${w.length - 2}, w${baseIdx+3}) = ${wordToHex(w7)}`);
      console.log(`\n>>> K${round} = ${wordToHex(w4)}${wordToHex(w5)}${wordToHex(w6)}${wordToHex(w7)}`);
      console.log();
    }

    console.log("\n========== HOÀN THÀNH SINH 10 KHÓA ==========");

  } catch (e) {
    console.error("Error:", e);
    process.exit(1);
  }
})();