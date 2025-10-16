// index.ts
import * as readline from "readline";
import { AES } from "./aes";
import { hexToBytes, isHexString, bytesToHex } from "./utils";

const rl = readline.createInterface({ input: process.stdin, output: process.stdout });

function question(prompt: string): Promise<string> {
  return new Promise(resolve => rl.question(prompt, ans => resolve(ans.trim())));
}

(async () => {
  try {
    const plaintextInput = await question("Enter plaintext (16 chars or 32 HEX): ");
    const keyInput = await question("Enter key (16 chars or 32 HEX): ");
    rl.close();

    let plaintextBytes: Uint8Array;
    let keyBytes: Uint8Array;

    // Determine plaintext format
    if (plaintextInput.length === 32 && isHexString(plaintextInput)) {
      plaintextBytes = hexToBytes(plaintextInput);
    } else if (plaintextInput.length === 16) {
      plaintextBytes = new Uint8Array(Buffer.from(plaintextInput, "utf8"));
    } else {
      throw new Error("Plaintext must be 16 chars or 32 HEX");
    }

    if (keyInput.length === 32 && isHexString(keyInput)) {
      keyBytes = hexToBytes(keyInput);
    } else if (keyInput.length === 16) {
      keyBytes = new Uint8Array(Buffer.from(keyInput, "utf8"));
    } else {
      throw new Error("Key must be 16 chars or 32 HEX");
    }

    const aes = new AES(keyBytes);
    // debug=true prints every step
    const cipher = aes.encrypt(plaintextBytes, true);

    console.log("\nFINAL CIPHERTEXT (HEX):", bytesToHex(cipher));
  } catch (e) {
    console.error("Error:", (e as Error).message);
    process.exit(1);
  }
})();
