#include <instructions.h>

/* 00E0	 cls	 Clear the screen */
INSTRUCTION(cls) {
  clear_screen(cpu->gfx); 
}

/* 00EE	 rts	 return from subroutine call */
INSTRUCTION(rts) {
   cpu->regs.pc = STACK_POP(cpu);
   
   if(IS_STACK_SMASHED(cpu->regs.sp)) {
      fprintf(stderr, "[Fatal Error] Stack smashing detected.\n");
      fprintf(stderr, "========== Memory Dump ===========\n");
      dump_memory(cpu);
      exit(1);
   }
}

/* 1xxx	 jmp xxx	 jump to address xxx */
INSTRUCTION(jmp) {
  cpu->regs.pc = cpu->opcode & 0xFFF;     
}

/* 2xxx	 jsr xxx	 jump to subroutine at address xxx */
INSTRUCTION(jsr) {
  STACK_PUSH(cpu, cpu->regs.pc);
  if(IS_STACK_SMASHED(cpu->regs.sp)) {
      fprintf(stderr, "[Fatal Error] Stack smashing detected.\n");
      fprintf(stderr, "========== Memory Dump ===========\n");
      dump_memory(cpu);
      exit(1);
   }

  cpu->regs.pc = cpu->opcode & 0xFFF;
}

/* 3rxx	 skeq vr,xx	 skip if register r = constant */
INSTRUCTION(skeq) {
  cpu->regs.v[((cpu->opcode & 0xF00) >> 8)] == (cpu->opcode & 0xFF) ? cpu->regs.pc += 2 : 0;
}

/* 4rxx	 skne vr,xx	 skip if register r <> constant */
INSTRUCTION(skne) {
  cpu->regs.v[((cpu->opcode & 0xF00) >> 8)] != (cpu->opcode & 0xFF) ? cpu->regs.pc += 2 : 0;
}

/* 5ry0	 skeq vr,vy	 skip f register r = register y */
INSTRUCTION(skeq2) {
  cpu->regs.v[((cpu->opcode & 0xF00) >> 8)] == cpu->regs.v[((cpu->opcode & 0x0F0) >> 4)] ? cpu->regs.pc += 2 : 0;
}

/* 6rxx	 mov vr,xx	 move constant to register r */
INSTRUCTION(mov) {
  cpu->regs.v[((cpu->opcode & 0xF00) >> 8)] = (cpu->opcode & 0xFF);
}

/* 7rxx	 add vr,xx	 add constant to register r	 No carry generated */
INSTRUCTION(add) {
  cpu->regs.v[((cpu->opcode & 0xF00) >> 8)] += (cpu->opcode & 0xFF);
}

/* 8ry0	 mov vr,vy	 move register vy into vr */
INSTRUCTION(mov2) {
  cpu->regs.v[((cpu->opcode & 0xF00) >> 8)] = cpu->regs.v[((cpu->opcode & 0xF0) >> 4)];
}

/* 8ry1	 or rx,ry	 or register vy into register vx */
INSTRUCTION(or) {
  cpu->regs.v[((cpu->opcode & 0xF00) >> 8)] |= cpu->regs.v[((cpu->opcode & 0xF0) >> 4)];
}

/* 8ry2	 and rx,ry	 and register vy into register vx */
INSTRUCTION(and) {
  cpu->regs.v[((cpu->opcode & 0xF00) >> 8)] &= cpu->regs.v[((cpu->opcode & 0xF0) >> 4)];
}

/* 8ry3	 xor rx,ry	 exclusive or register ry into register rx */
INSTRUCTION(xor) {
  cpu->regs.v[((cpu->opcode & 0xF00) >> 8)] ^= cpu->regs.v[((cpu->opcode & 0xF0) >> 4)];
}

/* 8ry4	 add vr,vy	 add register vy to vr,carry in vf */
INSTRUCTION(add2) {
  uint8_t add = cpu->regs.v[((cpu->opcode & 0xF00) >> 8)] + cpu->regs.v[((cpu->opcode & 0xF0) >> 4)];

  cpu->regs.v[0xF] = (add > 0xFF) ? 1 : 0; // carry bit in VF
  cpu->regs.v[((cpu->opcode & 0xF00) >> 8)] += add;
}

/* 8ry5	 sub vr,vy	 subtract register vy from vr,borrow in vf */
INSTRUCTION(sub) {
  uint8_t sub = cpu->regs.v[((cpu->opcode & 0xF00) >> 8)] - cpu->regs.v[((cpu->opcode & 0xF0) >> 4)];

  cpu->regs.v[0xF] = (sub < 0x0) ? 0 : 1; // borrow bit in VF
  cpu->regs.v[((cpu->opcode & 0xF00) >> 8)] -= sub;
}

/* 8r06	 shr vr	 shift register vy right, bit 0 goes into register vf */
INSTRUCTION(shr) {
  cpu->regs.v[0xF] = cpu->regs.v[((cpu->opcode & 0xFFF) >> 8)] & 1;
  cpu->regs.v[(cpu->opcode & 0xFFF) >> 8] >>= 1;
}

/* 8ry7	 rsb vr,vy	 subtract register vr from register vy, result in vr	 vf set to 1 if borrows */
INSTRUCTION(rsb) {
  uint8_t sub = cpu->regs.v[(cpu->opcode & 0xF0) >> 4] - cpu->regs.v[(cpu->opcode & 0xF00) >> 8];

  cpu->regs.v[0xF] = (sub < 0x0) ? 0 : 1; // borrow bit in VF
  cpu->regs.v[((cpu->opcode & 0xF00) >> 8)] -= sub;
}

/* 8r0e	 shl vr	 shift register vr left,bit 7 goes into register vf */
INSTRUCTION(shl) {
  uint8_t vr = cpu->regs.v[((cpu->opcode & 0xF00) >> 8)];

  cpu->regs.v[0xF] = (vr & 0x80) >> 7;
  cpu->regs.v[((cpu->opcode & 0xF00) >> 8)] <<= 1;
}

/* 9ry0	 skne rx,ry	 skip if register rx <> register ry */
INSTRUCTION(skne2) {
  ((cpu->opcode & 0xF00) >> 8) != ((cpu->opcode & 0xF0) >> 4) ? cpu->opcode += 2 : 0;
}

/* axxx	 mvi xxx	 Load index register with constant xxx */
INSTRUCTION(mvi) {
  cpu->regs.index = (cpu->opcode & 0xFFF);
}

/* bxxx	 jmi xxx	 Jump to address xxx+register v0 */
INSTRUCTION(jmi) {
  cpu->regs.pc = (cpu->opcode & 0xFFF) + cpu->regs.v[0];
}

/* crxx	 rand vr,xxx   	 vr = random number less than or equal to xxx */
INSTRUCTION(rand) {
  srand(time(NULL));
  cpu->regs.v[(cpu->opcode & 0xF00) >> 8] = rand() % ((cpu->opcode & 0xFFF) + 1);
}

/* drys	 sprite rx,ry,s	 Draw sprite at screen location rx,ry height s */
INSTRUCTION(sprite) {
  uint8_t height = cpu->opcode & 0xF;
  uint8_t x = cpu->regs.v[cpu->opcode & 0xF0 >> 4];
  uint8_t y = cpu->regs.v[cpu->opcode & 0xF00 >> 8];

  cpu->regs.v[0xF] = 0;

  uint8_t i, j;
  for (j = 0; j < height; ++j){
    for (i = 0; i < 8; ++i){
      uint8_t pixel = cpu->mem[cpu->regs.index + j];
      
      if(pixel & 0x80){
        if(is_pixel_set(cpu->gfx, x + i, y + j)) cpu->regs.v[0xF] = 1;
      
        set_pixel(cpu->gfx, x + i, y + j); 
      }
      
      pixel <<= 1;
    }
  }
  
}



/* ek9e	 skpr k	 skip if key (register rk) pressed */
INSTRUCTION(skpr) {

}

/* eka1	 skup k	 skip if key (register rk) not pressed */
INSTRUCTION(skup) {
  
}

/* fr07	 gdelay vr	 get delay timer into vr */
INSTRUCTION(gdelay) {
  cpu->regs.v[(cpu->opcode & 0xF00) >> 8] = cpu->delay_timer;  
}

/* fr0a	 key vr	 wait for for keypress,put key in register vr */
INSTRUCTION(key) {

}

/* fr15	 sdelay vr	 set the delay timer to vr */
INSTRUCTION(sdelay) {
  cpu->delay_timer = cpu->regs.v[(cpu->opcode & 0xF00) >> 8];
}

/* fr18	 ssound vr	 set the sound timer to vr */
INSTRUCTION(ssound) {
  cpu->regs.v[(cpu->opcode & 0xF00) >> 8] = cpu->sound_timer;
}

/* fr1e	 adi vr	 add register vr to the index register	 */
INSTRUCTION(adi) {
  cpu->regs.index += cpu->regs.v[(cpu->opcode & 0xF00) >> 8];
}

/* fr29	 font vr	 point I to the sprite for hexadecimal character in vr */
INSTRUCTION(font) {
  cpu->regs.index = cpu->regs.v[(cpu->opcode & 0xF00) >> 8];
}

/* fr30	 xfont vr	 point I to the sprite for hexadecimal character in vr */
INSTRUCTION(xfont) {
  cpu->regs.index = cpu->regs.v[(cpu->opcode & 0xF00) >> 8];
}

/* fr33	 bcd vr	 store the bcd representation of register vr at location I,I+1,I+2 */
INSTRUCTION(bcd) {
  
}

/* fr55	 str v0-vr	 store registers v0-vr in memory at location I onwards */
INSTRUCTION(str) {
  uint8_t i;
  for (i = 0x0; i < 0xF; ++i){
    cpu->mem[cpu->regs.index + i] = cpu->regs.v[i];
  }
}

/* fx65	 ldr v0-vr	 load registers v0-vr from memory at location I onwards */
INSTRUCTION(ldr) {
  uint8_t i;
  for (i = 0x0; i < 0xF; ++i){
    cpu->regs.v[i] = cpu->mem[cpu->regs.index + i];
  }  
}
