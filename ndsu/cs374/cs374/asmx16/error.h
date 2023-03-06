/*
 * ERROR.H
 *
 * Error Definition File
 */

#define ERR_NO_ARGUMENT			0
#define ERR_INVALID_EXT			1
#define ERR_FILE_OPENING		2
#define ERR_DIRECTIVE_MISSING		3
#define ERR_INVALID_DIRECTIVE		4
#define ERR_END_OF_FILE			5
#define ERR_MORE_THAN_ONE_PROGRAM	6
#define ERR_NO_PROGRAM			7
#define ERR_MORE_THAN_ONE_STACK		8
#define ERR_NO_STACK			9
#define ERR_INVALID_FILE		10

struct error_structure
{
    int nbr;
    char *text;
}

error_list[] =
{
    /* ERR_NO_ARGUMENT		 */
                    0, "No filename found on the command line",
    /* ERR_INVALID_EXT		 */
                    0, "Invalid file extension specified",
    /* ERR_FILE_OPENING	 */
                    0, "Unable to open file",
    /* ERR_DIRECTIVE_MISSING	 */
                    0, "Directive not found",
    /* ERR_INVALID_DIRECTIVE	 */
                    0, "Invalid directive",
    /* ERR_END_OF_FILE	 */
                    0, "Unexpected end of file",
    /* ERR_MORE_THAN_ONE_PROGRAM	 */
                    0, "More than one PROGRAM Directive",
    /* ERR_NO_PROGRAM	 */
                    0, "NO PROGRAM Directive",
    /* ERR_MORE_THAN_ONE_STACK	 */
                    0, "More than one STACK Directive",
    /* ERR_NO_STACK	 */
                    0, "NO STACK Directive",
    /* ERR_INVALID_FILE	 */
                    0, "Error while reading file"
};
