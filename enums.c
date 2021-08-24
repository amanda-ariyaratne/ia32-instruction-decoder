enum prefix {
    LOCK = 0xF0,
    REPNE = 0xF2,
    REP_REPE = 0xF3,
    SEG_CS = 0x2E,
    SEG_SS = 0x36,
    SEG_DS = 0x3E,
    SEG_ES = 0x26,
    SEG_FS = 0x64,
    SEG_GS = 0x65,
    OP_SIZE = 0x66,
    ADD_SIZE = 0x67
};

const int OP_2_BYTE_ESCAPE = 0x0F;
const int OP_3_BYTE_ESCAPE_1 = 0x38;
const int OP_3_BYTE_ESCAPE_2 = 0x3A;