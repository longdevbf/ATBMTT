// aes_utils.ts
export function hexToBytes(hex: string): Uint8Array {
  if (hex.length % 2 !== 0) throw new Error("hex string must have even length");
  const out = new Uint8Array(hex.length / 2);
  for (let i = 0; i < hex.length; i += 2) {
    out[i / 2] = parseInt(hex.substr(i, 2), 16);
  }
  return out;
}

export function bytesToHex(b: Iterable<number>): string {
  let s = "";
  for (const x of b) {
    s += x.toString(16).padStart(2, "0").toUpperCase();
  }
  return s;
}

export function isHexString(s: string): boolean {
  return /^[0-9a-fA-F]+$/.test(s);
}
