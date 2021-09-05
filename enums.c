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

enum i_prefix {
    i_NONE = 0,
    i_LOCK = 1,
    i_REPNE = 2,
    i_REP_REPE = 3,
    i_SEG_CS = 4,
    i_SEG_SS = 5,
    i_SEG_DS = 6,
    i_SEG_ES = 7,
    i_SEG_FS = 8,
    i_SEG_GS = 9,
    i_OP_SIZE = 10,
    i_ADD_SIZE = 11
};

const int OP_2_BYTE_ESCAPE = 0x0F;
const int OP_3_BYTE_ESCAPE_1 = 0x38;
const int OP_3_BYTE_ESCAPE_2 = 0x3A;