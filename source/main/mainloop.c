/* openAPL, Copyright (C) Branko Bratkovic 1999
 * This file is free software and is covered by the GNU General
 * Public License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
 *
 * For more details see the GNU General Public License (GPL) in
 * the docs directory.
 */
#include "memory.h"
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "apl.h"
#include "main.h"
#include "print.h"
#include "utility.h"
#include "parser.h"
#include "execute.h"
#include "getinput.h"

void mainloop()
{
    Context* thisContext;

    while (1) {
        /* if a function has been suspended
         * then create a new context
         */
        if (gsip->Mode != immed) {
            thisContext = (Context*)alloc(sizeof(Context));
            thisContext->Mode = immed;
            thisContext->suspended = 0;
            thisContext->prev = gsip;
            thisContext->text = (char*)NULL;
            thisContext->pcode = (char*)NULL;
            //thisContext->xref=(char *)NULL;
            //setjmp(thisContext->env);    /* come back here after longjmp() */
            thisContext->sp = sp;
            gsip = thisContext;
        }

        gsip->Mode = immed;
        if (gsip->pcode)
            aplfree((int*)gsip->pcode);
        gsip->pcode = (char*)NULL;
        if (gsip->text)
            aplfree((int*)gsip->text);
        gsip->text = (char*)NULL;

        lineNumber = -1;
        if (echoflg)
            echoflg = 1; /* enabled echo echo suppress off */
        checksp();       /* check for stack overflow */
        if (intflg)
            error(ERR_interrupt, "");

        /*  get a line of input */
        if (isatty(0))
            gsip->text = getinput("        ");
        else
            gsip->text = getinput("");
        /* getinput will return NULL at eof but only if input is not
       * from the keyboard.  The following will cause an exit
       * when input is from a file or a pipe
       */
        if (gsip->text == NULL)
            Exit(0);
        if (echoflg)
            printLine(gsip->text);

        /* compile the input */
        sandbox = sandboxflg;
        compile_new(CompileImmediate);
        if (gsip->pcode == 0)
            error(ERR_syntax, ""); //control returns to top of this file

        /* execute the compiled pseudo code */
        column = 0; /* prepare to print the results */
        execute();
    }
}
