/************************************************************************
 Ficheiro de implementação do Tipo de Dados Abstracto Data (date.c).
 A estrutura de dados de suporte do tempo é um registo constituído pelos
 três campos de tipo inteiro Day, Month e Year.

 Autor : Pedro Veloso Teixeira                             NMEC : 84715
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "date.h" /* Ficheiro de interface do TDA - ADT Interface file */

/*************** Definição da Estrutura de Dados da Data ***************/

struct date
{
	unsigned int Day; unsigned int Month; unsigned int Year;
};

/******************** Controlo Centralizado de Erro ********************/

static unsigned int Error = OK;	/* inicialização do erro */

static char *ErrorMessages[] = { "sem erro", "data inexistente",
"memoria esgotada", "data invalida",
"ponteiro inexistente" };

static char *AbnormalErrorMessage = "erro desconhecido";

/*********** Número de mensagens de erro previstas no módulo ***********/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/***************** Protótipos dos Subprogramas Internos ****************/

static int LeapYear (int); /* ano bissexto */
static int ValidDate (int, int, int); /* validar data */

/********************** Definição dos Subprogramas *********************/

void DateClearError (void)
{ Error = OK; }

int DateError (void)
{ return Error; }

char *DateErrorMessage (void)
{
	if (Error < N) return ErrorMessages [Error];
	else return AbnormalErrorMessage; /* sem mensagem de erro */
}

PtDate DateCreate (int pday, int pmonth, int pyear) /* construtor inicializador */
{
	// Validate Date
	if (!ValidDate(pday, pmonth, pyear)) {
		Error = INVALID;
		return NULL;
	}

	// If the date is valid, create it
	PtDate date = malloc(sizeof (struct date));

	// Error: no available memory
	if (date == NULL) {
		Error = NO_MEM;
		return NULL;
	}

    // Available Memory -> Create the Date
	date -> Day = pday;
	date -> Month = pmonth;
	date -> Year = pyear;

	Error = OK;

	return date;
}

void DateDestroy (PtDate *pdate) /* destrutor */
{
	PtDate pointer = *pdate;

	// Verify if the date referenced by the pointer exists
	if (pointer == NULL) {
		Error = NO_DATE;
		return;
	}

 	// If exists, free up the space
	free(pointer);
	Error = OK;
	*pdate = NULL;
}

PtDate DateStringCreate (char *pstrdate) /* construtor a partir de uma string */
{
	if (pstrdate == NULL) { Error = NULL_PTR; return NULL; }
	if (strlen (pstrdate) != 10) { Error = INVALID; return NULL; }

	char * date[4]; int i = 0;

	date[i] = strtok (pstrdate, "-");
	while (date[i] != NULL) date[++i] = strtok (NULL, "-");

	if (i != 3) { Error = INVALID; return NULL; }

	int Year, Month, Day;
	sscanf (date[0], "%d", &Year);
	sscanf (date[1], "%d", &Month);
	sscanf (date[2], "%d", &Day);

	return DateCreate (Day, Month, Year);
}

PtDate DateCopy (PtDate pdate)	/* construtor cópia */
{
	if (pdate == NULL) { Error = NO_DATE; return NULL; }
	else return DateCreate (pdate->Day, pdate->Month, pdate->Year);
}

int DateGetYear (PtDate pdate) /* observador do ano */
{
    // Verify if pdate exists
	if (pdate == NULL) {
		Error = NO_DATE;
		return 0;
	}

	Error = OK;
	return pdate -> Year;
}

int DateGetMonth (PtDate pdate) /* observador do mês */
{
	if (pdate == NULL) { Error = NO_DATE; return 0; }
	else { Error = OK; return pdate->Month; }
}

int DateGetDay (PtDate pdate) /* observador do dia */
{
 	// Verify if pdate exists
	if (pdate == NULL) {
		Error = NO_DATE;
		return 0;
	}

	Error = OK;
	return pdate -> Day;
}

void DateSet (PtDate pdate, int pday, int pmonth, int pyear) /* modificador da data */
{
  // Verify if pdate exists
	if (pdate == NULL) {
		Error = NO_DATE;
		return;
	}

  // Verify if the given date would be valid
	if (!ValidDate(pday, pmonth, pyear)) {
		Error = INVALID;
		return;
	}

  // Sets the new date
	pdate -> Day   = pday;
	pdate -> Month = pmonth;
	pdate -> Year  = pyear;
	Error = OK;
}

int DateEquals (PtDate pdate1, PtDate pdate2)  /* comparador de igualdade */
{
  // Verify if pdate1 and pdate2 exists
	if (pdate1 == NULL || pdate2 == NULL) {
		Error = NO_DATE;
		return 0;
	}

	// Verify if the arguments are pointers to the same reference
  // If so, the dates are the same
	if (pdate1 == pdate2) {
		Error = OK;
		return 1;
	}

	// Verify if the arguments are pointers to valid dates
	if (!ValidDate(DateGetDay(pdate1), DateGetMonth(pdate1), DateGetYear(pdate1)) || !ValidDate(DateGetDay(pdate2), DateGetMonth(pdate2), DateGetYear(pdate2))) {
		Error = INVALID;
		return 0;
	}

	// If not, uses the DateCompareTo function to evaluate
	Error = OK;
	return DateCompareTo (pdate1, pdate2) == 0;
}

int DateCompareTo (PtDate pdate1, PtDate pdate2)  /* operador relacional (> == <) */
{
	/* Initial verifications -> a good modularization would mean these checks
	 * would be part of a function. I chose not to create the said function
	 * to avoid changing the file beyond what's asked */

	 // Verify if pdate1 and pdate2 exists
	if (pdate1 == NULL || pdate2 == NULL) {
		Error = NO_DATE;
		return 0;
	}

	// Verify if the arguments are pointers to the same reference
 	// If so, the dates are the same
	if (pdate1 == pdate2) {
		Error = OK;
		return 1;
	}

 	// Verify if the arguments are pointers to valid dates
	int year1 = DateGetYear(pdate1);
	int year2 = DateGetYear(pdate2);
	int month1 = DateGetMonth(pdate1);
	int month2 = DateGetMonth(pdate2);
	int day1 = DateGetDay(pdate1);
	int day2 = DateGetDay(pdate2);

	if (!ValidDate(day1, month1, year1) || !ValidDate(day2, month2, year2)) {
		Error = INVALID;
		return 0;
	}

	// Dates are valid --> Verify years
	Error = OK;
	if (year1 < year2) {
		return -1;
	}
	else if (year1 > year2) {
		return 1;
	}
	// Years are the same --> Verify months
	else {
		if (month1 < month2) {
			return -1;
		}
		else if (month1 > month2) {
			return 1;
		}
		// Months are the same --> Verify days
		else {
			if (day1 < day2) {
				return -1;
			}
			else if (day1 > day2) {
				return 1;
			}
			else {
				return 0;
			}
		}
	}
}

int DateDayMonth (int pmonth, int pyear) /* dias de um mês */
{
	int MonthDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (pmonth == 2 && LeapYear(pyear)) return 29;
	Error = OK;
	return MonthDays[pmonth-1];
}

char * DateToString (PtDate pdate)  /* data no formato dd/mm/yyyy */
{
	/* verifica se a data existe - verifies if date exists */
	if (pdate == NULL) { Error = NO_DATE; return NULL; }

	char * Str;
	/* cria a sequência de caracteres - allocating the string */
	if ((Str = calloc (11, sizeof (char))) == NULL)
		{ Error = NO_MEM; return NULL; }

	sprintf (Str, "%02d/%02d/%04d", pdate->Day, pdate->Month, pdate->Year);
	Error = OK;
	return Str;
}

char * DateToFullString (PtDate pdate)  /* data por extenso */
{
	char* FullMonth[] = {"janeiro", "fevereiro", "março", "abril",
	"maio", "junho", "julho", "agosto",
	"setembro", "outubro", "novembro", "dezembro"};

	/* verifica se a data existe - verifies if date exists */
	if (pdate == NULL) { Error = NO_DATE; return NULL; }

	char * Str;
	/* cria a sequência de caracteres - allocating the string */
	if ((Str = calloc (23, sizeof (char))) == NULL)
		{ Error = NO_MEM; return NULL; }

	sprintf (Str, "%02d de %s de %04d", pdate->Day, FullMonth[pdate->Month-1], pdate->Year);
	Error = OK;
	return Str;
}

PtDate DateTomorrow (PtDate pdate)  /* nova data com o dia seguinte */
{
	// Verify if pdate exists
	if (pdate == NULL) {
		Error = NO_DATE;
		return NULL;
	}

	int day = DateGetDay(pdate);
	int month = DateGetMonth(pdate);
	int year = DateGetYear(pdate);

	// Verify if date is valid
	if (!ValidDate(day, month, year)) {
		Error = INVALID;
		return NULL;
	}

	Error = OK;
	
	if (day == DateDayMonth(month, year)) {
		if (month == 12) return DateCreate(1, 1, year + 1);
		return DateCreate(1, month + 1, year);
	}
	return DateCreate(day + 1, month, year);

}

PtDate DateYesterday (PtDate pdate)  /* nova data com o dia anterior */
{
	 // Verify if pdate exists
	if (pdate == NULL) {
		Error = NO_DATE;
		return NULL;
	}

	int day = DateGetDay(pdate);
	int month = DateGetMonth(pdate);
	int year = DateGetYear(pdate);

	// Verify if date is valid
	if (!ValidDate(day, month, year)) {
		Error = INVALID;
		return NULL;
	}

	Error = OK;

	if (day == 1) {
		if (month == 1) return DateCreate(31, 12, year - 1);
		return DateCreate(DateDayMonth(month-1, year), month - 1, year);
	}
	return DateCreate(day - 1, month, year);

}

/*************** Implementação dos Subprogramas Internos ***************/

/*******************************************************************************
 Função auxiliar que verifica se um ano é bissexto. Devolve 1 em caso afirmativo
  e 0 em caso contrário. Valores de erro: OK.

 Auxiliary function to verify if a year is a leap year. Returns 1 in affirmative
 case and 0 otherwise. Error codes: OK.
*******************************************************************************/
static int LeapYear (int pyear)
{
	Error = OK;
	return ((pyear % 4 == 0) && (pyear % 100 != 0)) || (pyear % 400 == 0);
}

/*******************************************************************************
 Função auxiliar que verifica se uma data definida por dia, mês e ano é válida.
 Devolve 1 em caso afirmativo e 0 em caso contrário. Valores de erro: OK ou INVALID.

 Auxiliary function to verify if a date defined by day, month and year is valid.
 Returns 1 in affirmative case and 0 otherwise. Error codes: OK or INVALID.
*******************************************************************************/

static int ValidDate (int pday, int pmonth, int pyear)
{
	int leapyear;

	Error = OK;
	switch (pmonth)
	{
		case  1:
		case  3:
		case  5:
		case  7:
		case  8:
		case 10:
		case 12: if (pday < 1 || pday > 31) Error = INVALID;
		break;
		case  4:
		case  6:
		case  9:
		case 11: if (pday < 1 || pday > 30) Error = INVALID;
		break;
		case  2: leapyear = LeapYear (pyear);
		if (pday < 1 || (pday > 29 && leapyear) || (pday > 28 && !leapyear))
			Error = INVALID;
		break;
	}
	if (Error == OK) return 1; else return 0;
}
