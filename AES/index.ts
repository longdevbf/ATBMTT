import * as readline from "readline";
import { hexToByte } from "./utils";
import { keyExpansion, addRoundKey, subBytes, shiftRows, mixColumns, printStateMatrix } from "./aes";

async function question(prompt: string): Promise<string> {
  const rl = readline.createInterface({ input: process.stdin, output: process.stdout });
  return new Promise(resolve => rl.question(prompt, ans => { rl.close(); resolve(ans.trim()); }));
}

(async () => {
  try {
    const keyInput = await question("Nhap 32 ky tu hex cho AES128 key: ");
    const stateInput = await question("Nhap 32 ky tu hex cho state ban dau: ");

    if (keyInput.length !== 32 || stateInput.length !== 32) {
      console.error("Loi: phai nhap dung 32 ky tu hex cho key va state");
      process.exit(1);
    }

    const key = new Array(16).fill(0);
    const state = new Array(16).fill(0);
    for (let i = 0; i < 16; i++) {
      key[i] = hexToByte(keyInput.substr(i*2,2));
      state[i] = hexToByte(stateInput.substr(i*2,2));
    }

    const w: number[][] = new Array(44);
    for (let i = 0; i < 44; i++) w[i] = new Array(4).fill(0);

    keyExpansion(key, w);

    addRoundKey(state, w, 0);
    printStateMatrix(state, 0);

    for (let round = 1; round <= 9; round++) {
      subBytes(state);
      shiftRows(state);
      mixColumns(state);
      addRoundKey(state, w, round);
      printStateMatrix(state, round);
    }

    subBytes(state);
    shiftRows(state);
    addRoundKey(state, w, 10);
    printStateMatrix(state, 10);

  } catch (e) {
    console.error("Error:", e);
    process.exit(1);
  }
})();
