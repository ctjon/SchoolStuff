                   INTERNAL SUBROUTINES

    THIS DISCUSSION SHOWS YOU HOW TO IMPLEMENT PROGRAM MODULES IN THE
FORM OF INTENAL SUBROUTINES. LATER ON IN THE COURSE, WE WILL STUDY
EXTERNAL SUBROUTINES. THE FOLLOWING PROGRAM INDICATES USE OF INSTRUCTIONS
FOR TRANSFER OF CONTROL TO AN INTERNAL SUBROUTINE AND RETURN TO THE MAIN
SEGMENT.

MAIN     START
         BALR   12,0     .REG 12 IS THE BASE REGISTER
         USING  *,12
         ST     14,SAVE  .SAVE OPERATING SYSTEM RETURN ADDRESS
                .
                .
         L      15,=A(SUBRT)
         BALR   14,15         . SUBROUTINE CALL
                .             . RETURN FROM SUBRT AT THIS ADDRESS
                .
                .
         L      14,SAVE       .LOAD OP. SYS. RETURN ADDR
         BR     14            .RETURN CONTROL TO OP. SYS.
SUBRT    ....   ....          .SUBRT BODY
                .
                .
         BR     14            .RETURN TO CALLING ROUTINE
                .
                .             .OTHER MODULES
                .
SAVE     DS     F
                .
         LTORG
         END

    THE LTORG PSEUDO-OP WILL ACCUMULATE ALL THE LITERALS AT THE POINT
THE PSEUDO-OP OCCURS.
