import { sbox, Rcon } from "./aes_tables";

export type Byte = number;

export function hexToByte(hex: string): Byte {
  return parseInt(hex, 16) & 0xFF;
}

export function rotWord(w: number[]) {
  const t = w[0];
  w[0] = w[1]; w[1] = w[2]; w[2] = w[3]; w[3] = t;
}

export function subWord(w: number[]) {
  for (let i = 0; i < 4; i++) w[i] = sbox[w[i]];
}

export function xorRcon(w: number[], round: number) {
  w[0] ^= Rcon[round];
}

export function G(w: number[], round: number) {
  rotWord(w);
  subWord(w);
  xorRcon(w, round);
}

export function mul02(x: Byte): Byte {
  const res = ((x << 1) & 0xFF) ^ ((x & 0x80) ? 0x1B : 0x00);
  return res & 0xFF;
}

export function mul03(x: Byte): Byte {
  return (mul02(x) ^ x) & 0xFF;
}
