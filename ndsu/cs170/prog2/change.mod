MODULE CH1;

(* CHRISTOPHER C. TJON  *)
(* 110975-8             *)
(* CS170                *)
(* DR. ERICKSON         *)
(* 26 SEPTEMBER 1989    *)

(* THIS PROGRAM IS DESIGNED TO CALCULATE THE NUMBER OF *)
(* EACH OF THE VARIOUS TYPES OF COINS WHICH SHOULD BE  *)
(* RETURNED AS CHANGE FOR A GIVEN SALE.                *)

(* THE VARIABLES:                                      *)
(*     SALE     = THE AMOUNT OF THE SALE MADE          *)
(*     RECEIVED = THE AMOUNT OF CASH RECEIVED          *)
(*     CHANGE   = THE DOLLAR AMOUNT OF CHANGE          *)
(*     DOLLARS  = THE NUMBER OF DOLLAR BILLS RETURNED  *)
(*     QUARTERS = THE NUMBER OF QUARTERS RETURNED      *)
(*     DIMES    = THE NUMBER OF DIMES RETURNED         *)
(*     NICKELS  = THE NUMBER OF NICKELS RETURNED       *)
(*     PENNIES  = THE NUMBER OF PENNIES RETURNED       *)
(*     EXCESS   = A CARRIER VARIABLE USED FOR          *)
(*                CALCULATION OF EACH OF THE ABOVE     *)

FROM InOut IMPORT WriteLn, WriteString;

FROM RealInOut IMPORT WriteReal, ReadReal;


VAR DOLLARS, QUARTERS, DIMES, NICKELS, PENNIES,
    SALE,RECEIVED,CHANGE,EXCESS,SUM:REAL;

(* GET INPUT *)

BEGIN
    WriteString("PLEASE ENTER THE AMOUNT OF THE SALE: ");
    WriteLn;
    ReadReal(SALE);
    WriteLn;

    WriteString("PLEASE ENTER THE AMOUNT OF CASH RECEIVED: ");
    WriteLn;
    ReadReal(RECEIVED);
    WriteLn;

(* BEGIN CALCULATIONS *)

SUM := 0.0;

    CHANGE := RECEIVED - SALE;



    DOLLARS := (FLOAT(TRUNC(CHANGE)));
    EXCESS := CHANGE - DOLLARS;

    SUM := SUM + DOLLARS;

    QUARTERS := (FLOAT(TRUNC(EXCESS / 0.25)));
    EXCESS := EXCESS -(QUARTERS* 0.25);

    SUM := SUM + (QUARTERS*0.25);

    DIMES := (FLOAT(TRUNC(EXCESS / 0.10)));
    EXCESS := EXCESS - (DIMES * 0.10);

    SUM := SUM + (DIMES * 0.10);

    NICKELS := (FLOAT(TRUNC(EXCESS / 0.05)));
    EXCESS := EXCESS - (NICKELS * 0.05);

SUM := SUM + (NICKELS * 0.05);

    PENNIES :=  FLOAT(TRUNC((RECEIVED - SUM - SALE)*100.0));

(* END OF CALCULATIONS *)

(* WRITE OUTPUTS *)

WriteString("THE AMOUNT OF THE SALE IS: ");
WriteReal(SALE,6);
WriteLn;

WriteString("THE AMOUNT OF CASH RECEIVED IS: ");
WriteReal(RECEIVED,6);
WriteLn;

WriteString("THE FOLLOWING DENOMINATIONS SHOULD BE RETURNED: ");
WriteLn;

WriteString("DOLLARS: ");
WriteReal(DOLLARS,6);
WriteLn;

WriteString("QUARTERS: ");
WriteReal(QUARTERS,2);
WriteLn;

WriteString("DIMES: ");
WriteReal(DIMES,2);
WriteLn;

WriteString("NICKELS: ");
WriteReal(NICKELS,2);
WriteLn;

WriteString("PENNIES: ");
WriteReal(PENNIES,2);
WriteLn;

END CH1.
