/*
 * TABLES.H
 *
 * Symbol Table Definition File
 */

#define	TYPE_NONE	0
#define TYPE_EXTERNAL	1
#define TYPE_INTERNAL	2
#define TYPE_PUBLIC	3

/*
 * Symbol Table Structure
 */
struct symbol_entry
{
    struct symbol_entry *next;
    char *name;
    int value;
    int location;
    char *type1;
    int type;
    int used;
};

struct symbol_entry symbol_anchor;


/*
 * Opcode Table Structure
 */
struct opcode_entry
{
    char *name;
    short value;
    short length;
};

/*
 * Static X16 OpCode Table
 */
struct opcode_entry opcode_table[] =
{
 {"MOVB", 0x0F, 4},
 {"MOVH", 0x0E, 4},
 {"CMPB", 0x0D, 4},
 {"CMPH", 0x0C, 4},
 {"ADDB", 0x05, 4},
 {"ADDH", 0x04, 4},
 {"ADCB", 0x07, 4},
 {"ADCH", 0x06, 4},
 {"SUBB", 0x09, 4},
 {"SUBH", 0x08, 4},
 {"SBBB", 0x0B, 4},
 {"SBBH", 0x0A, 4},
 {"INPB", 0x0F, 4},
 {"INPH", 0x0E, 4},
 {"OUTB", 0x0F, 4},
 {"OUTH", 0x0E, 4},
 {"NOTB", 0x1C, 7},
 {"NOTH", 0x14, 7},
 {"ANDB", 0x18, 7},
 {"ANDH", 0x10, 7},
 {"IORB", 0x19, 7},
 {"IORH", 0x11, 7},
 {"XORB", 0x1A, 7},
 {"XORH", 0x12, 7},
 {"TSTB", 0x1B, 7},
 {"TSTH", 0x13, 7},
 {"NEGB", 0x1D, 7},
 {"NEGH", 0x15, 7},
 {"MULB", 0x1E, 7},
 {"MULH", 0x16, 7},
 {"DIVB", 0x1F, 7},
 {"DIVH", 0x17, 7},
 {"BREQ", 0x1C, 10},
 {"BRNE", 0x14, 10},
 {"BUGT", 0x15, 10},
 {"BULE", 0x1D, 10},
 {"BULT", 0x19, 10},
 {"BUGE", 0x11, 10},
 {"BSGT", 0x16, 10},
 {"BSLE", 0x1E, 10},
 {"BSLT", 0x1B, 10},
 {"BSGE", 0x13, 10},
 {"BRNG", 0x1A, 10},
 {"BRNN", 0x12, 10},
 {"BROV", 0x18, 10},
 {"BRNV", 0x10, 10},
 {"BRUN", 0x1F, 10},
 {"SLLB", 0x70, 10},
 {"SLLH", 0x30, 10},
 {"SALB", 0x72, 10},
 {"SALH", 0x32, 10},
 {"SLRB", 0x71, 10},
 {"SLRH", 0x31, 10},
 {"SARB", 0x73, 10},
 {"SARH", 0x33, 10},
 {"ROLB", 0x78, 10},
 {"ROLH", 0x38, 10},
 {"RORB", 0x79, 10},
 {"RORH", 0x39, 10},
 {"RCLB", 0x7A, 10},
 {"RCLH", 0x3A, 10},
 {"RCRB", 0x7B, 10},
 {"RCRH", 0x3B, 10},
 {"NOOP", 0x00, 16},
 {"HALT", 0x01, 16},
 {"SCRY", 0x31, 16},
 {"CCRY", 0x30, 16},
 {"INTF", 0x10, 16},
 {"CALL", 0x02, 16},
 {"RETN", 0x03, 16},
 {"IRET", 0x07, 16},
 {"INTR", 0x04, 16},
 {"TESB", 0x05, 16},
 {"PSHB", 0x0F, 4},
 {"PSHH", 0x0E, 4},
 {"POPB", 0x0F, 4},
 {"POPH", 0x0E, 4},
 {"PSHP", 0x0E, 4},
 {"POPP", 0x0E, 4},
 {"", 0x00, 0}
};


/*
 * X16 Addressing Mode Table
 */
#define NO_OPERAND		-1    /* used when there is no operand        */
#define	MODE_IMM3		0x02  /* 3 bit immediate designation          */
#define	MODE_IMM6		0x3a  /* 6 bit immediate designation          */
#define	MODE_REG     		0x00  /* register designation                 */
#define MODE_DIR3		0x03  /* 3 bit direct designation             */
#define MODE_DIR6_MEM		0x3b  /* 6 bit direct to memory designation   */
#define MODE_DIR6_IO		0x03  /* 6 bit direct to I/O port designation */
#define MODE_REG_IND		0x01	/* register indirect designation      */
#define MODE_REG_IND_INC	0x05	/* reg indirect autoinc designation   */
#define MODE_REG_IND_DEC	0x07	/* reg indirect autodec designation   */
#define MODE_REL   		0x06	/* relative designation               */


/*
 * X16 Register Definitions
 */
#define REG_ERR			-1	/* error */
#define REG_R0			0x00	/* Register 0 */
#define REG_R1			0x01	/* Register 1 */
#define REG_R2			0x02	/* Register 2 */
#define REG_R3			0x03	/* Register 3 */
#define REG_R4			0x04	/* Register 4 */
#define REG_R5			0x05	/* Register 5 */
#define REG_SP			0x06	/* Stack Pointer */
#define REG_PC			0x07	/* Program Counter */

/*
 * Directive Table Structure
 */
struct dir_entry
{
    char *name;
    int length;
};

/*
 * Static X16 Directive Table
 */
#define	DIR_DB		"DB"
#define	DIR_DH		"DH"
#define	DIR_DW		"DW"
#define	DIR_DD		"DD"
#define	DIR_ORG		"ORG"
#define	DIR_EQU		"EQU"
#define	DIR_UNIT	"UNIT"
#define	DIR_END		"END"
#define	DIR_PROGRAM	"PROGRAM"
#define	DIR_PROCEDURE	"PROCEDURE"
#define DIR_EXTERNAL	"EXTERNAL"
#define DIR_PUBLIC	"PUBLIC"
#define	DIR_ENDP	"ENDP"
#define	DIR_MACRO	"MACRO"
#define	DIR_ENDM	"ENDM"

struct dir_entry dir_table[] =
{
 {DIR_DB},
 {DIR_DH},
 {DIR_DW},
 {DIR_DD},
 {DIR_ORG},
 {DIR_EQU},
 {DIR_UNIT},
 {DIR_END},
 {DIR_PROGRAM},
 {DIR_PROCEDURE},
 {DIR_ENDP},
 {DIR_MACRO},
 {DIR_ENDM},
 {""}
};


/*
 * X16 Assembly Code Line Structure - info about a line of code
 */
struct line_info
{
    int addr;
    int error;
    int opcode;
    int oper1;
    int oper2;
    int r;
    int n;
    char extra[80];
    int prefix;
};
