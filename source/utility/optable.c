/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

/*
 * Declarations of all functions (required by Version 7 C
 * for the array to be set up without warning messages)
 */

extern int ex_abs();
extern int ex_add();
extern int ex_and();
extern int ex_ap();
extern int ex_arg1();
extern int ex_arg2();
extern int ex_asgn();
extern int ex_auto();
extern int ex_base();
extern int ex_botch();
extern int ex_br();
extern int ex_br0();
extern int ex_cat();
extern int ex_catk();
extern int ex_ceil();
extern int ex_chdir();
extern int ex_cir();
extern int ex_close();
extern int ex_com();
extern int ex_com0();
extern int ex_comb();
extern int ex_comk();
extern int ex_creat();
extern int ex_crp();
extern int ex_ddom();
extern int ex_deal();
extern int ex_dfmt();
extern int ex_dibm();
extern int ex_diot();
extern int ex_div();
extern int ex_drho();
extern int ex_drop();
extern int ex_dtrn();
extern int ex_dup();
extern int ex_elid();
extern int ex_eps();
extern int ex_eq();
extern int ex_exd();
extern int ex_exd0();
extern int ex_exdk();
extern int ex_exec();
extern int ex_exit();
extern int ex_exp();
extern int ex_fac();
extern int ex_fdef();
extern int ex_float();
extern int ex_nl();
extern int ex_floor();
extern int ex_fork();
extern int ex_fun();
extern int ex_gdd();
extern int ex_gddk();
extern int ex_gdu();
extern int ex_gduk();
extern int ex_ge();
extern int ex_gt();
extern int ex_hprint();
extern int ex_ibr();
extern int ex_ibr0();
extern int ex_syscom();
extern int ex_index();
extern int ex_iprod();
extern int ex_kill();
extern int ex_label();
extern int ex_le();
extern int ex_log();
extern int ex_loge();
extern int ex_lt();
extern int ex_max();
extern int ex_mdom();
extern int ex_menc();
extern int ex_execute();
extern int ex_mfmt();
extern int ex_mibm();
extern int ex_min();
extern int ex_minus();
extern int ex_miot();
extern int ex_mod();
extern int ex_mrho();
extern int ex_mtrn();
extern int ex_mul();
extern int ex_nand();
extern int ex_nc();
extern int ex_ne();
extern int ex_nilret();
extern int ex_nor();
extern int ex_not();
extern int ex_open();
extern int ex_oprod();
extern int ex_or();
extern int ex_pi();
extern int ex_pipe();
extern int ex_plus();
extern int ex_print();
extern int ex_pwr();
extern int ex_quad();
extern int ex_qquad();
extern int ex_qav();
extern int ex_qct();
extern int ex_qio();
extern int ex_qlx();
extern int ex_qpp();
extern int ex_qpw();
extern int ex_qts();
extern int ex_rand();
extern int ex_rav();
extern int ex_ravk();
extern int ex_rd();
extern int ex_read();
extern int ex_recip();
extern int ex_red();
extern int ex_red0();
extern int ex_redk();
extern int ex_rep();
extern int ex_rest();
extern int ex_rev();
extern int ex_rev0();
extern int ex_revk();
extern int ex_rot();
extern int ex_rot0();
extern int ex_rotk();
extern int ex_run();
extern int ex_scan();
extern int ex_scn0();
extern int ex_scnk();
extern int ex_seek();
extern int ex_sgn();
extern int ex_signl();
extern int ex_sub();
extern int ex_take();
extern int ex_unlink();
extern int ex_wait();
extern int ex_write();
extern int ex_ex();
extern int ex_qai();
extern int ex_qargv();

/* WARNING, the following must agree with opt_codes.h and code_dump.c */
int (*exop[])() = {

    0,          /* 0 */
    0,          /* 1 */
    ex_add,     /* 2 */
    ex_plus,    /* 3 */
    ex_sub,     /* 4 */
    ex_minus,   /* 5 */
    ex_mul,     /* 6 */
    ex_sgn,     /* 7 */
    ex_div,     /* 8 */
    ex_recip,   /* 9 */
    ex_mod,     /* 10 */
    ex_abs,     /* 11 */
    ex_min,     /* 12 */
    ex_floor,   /* 13 */
    ex_max,     /* 14 */
    ex_ceil,    /* 15 */
    ex_pwr,     /* 16 */
    ex_exp,     /* 17 */
    ex_log,     /* 18 */
    ex_loge,    /* 19 */
    ex_cir,     /* 20 */
    ex_pi,      /* 21 */
    ex_comb,    /* 22 */
    ex_fac,     /* 23 */
    ex_deal,    /* 24 */
    ex_rand,    /* 25 */
    ex_drho,    /* 26 */
    ex_mrho,    /* 27 */
    ex_diot,    /* 28 */
    ex_miot,    /* 29 */
    ex_rot0,    /* 30 */
    ex_rev0,    /* 31 */
    ex_dtrn,    /* 32 */
    ex_mtrn,    /* 33 */
    ex_dibm,    /* 34 */
    ex_mibm,    /* 35 */
    ex_gdu,     /* 36 */
    ex_gduk,    /* 37 */
    ex_gdd,     /* 38 */
    ex_gddk,    /* 39 */
    ex_exd,     /* 40 */
    ex_scan,    /* 41 */
    ex_exdk,    /* 42 */
    ex_scnk,    /* 43 */
    ex_iprod,   /* 44 */
    ex_oprod,   /* 45 */
    ex_quad,    /* 46 */
    ex_qquad,   /* 47 */
    ex_br0,     /* 48 */
    ex_br,      /* 49 */
    ex_ddom,    /* 50 */
    ex_mdom,    /* 51 */
    ex_com,     /* 52 */
    ex_red,     /* 53 */
    ex_comk,    /* 54 */
    ex_redk,    /* 55 */
    ex_rot,     /* 56 */
    ex_rev,     /* 57 */
    ex_rotk,    /* 58 */
    ex_revk,    /* 59 */
    ex_cat,     /* 60 */
    ex_rav,     /* 61 */
    ex_catk,    /* 62 */
    ex_ravk,    /* 63 */
    ex_print,   /* 64 */
    0,          /* 65 */
    ex_elid,    /* 66 */
    0,          /* 67 */
    0,          /* 68 */
    ex_index,   /* 69 */
    ex_hprint,  /* 70 */
    ex_lt,      /* 71 */
    ex_le,      /* 72 */
    ex_gt,      /* 73 */
    ex_ge,      /* 74 */
    ex_eq,      /* 75 */
    ex_ne,      /* 76 */
    ex_and,     /* 77 */
    ex_or,      /* 78 */
    ex_nand,    /* 79 */
    ex_nor,     /* 80 */
    ex_not,     /* 81 */
    ex_eps,     /* 82 */
    ex_execute, /* 83 */
    ex_rep,     /* 84 */
    ex_take,    /* 85 */
    ex_drop,    /* 86 */
    ex_exd0,    /* 87 */
    ex_asgn,    /* 88 */
    ex_syscom,  /* 89 */
    0,          /* 90 */
    0,          /* 91 */
    ex_fun,     /* 92 */
    ex_arg1,    /* 93 */
    ex_arg2,    /* 94 */
    ex_auto,    /* 95 */
    ex_rest,    /* 96 */
    ex_com0,    /* 97 */
    ex_red0,    /* 98 */
    ex_exd0,    /* 99 */
    ex_scn0,    /*100 */
    ex_base,    /*101 */
    ex_menc,    /*102			monadic encod   */
    ex_label,   /*103 */
    0,          /*104 */
    ex_qlx,     /* 105 Quad Latent eXpression */
    ex_qav,     /* 106 Quad Atomic Vector */
    ex_qts,     /* 107 Quad Time Stamp */
    ex_qpp,     /* 108 Quad Print Precision */
    ex_qpw,     /* 109 Quad Print Width */
    ex_qct,     /* 110 Quad Comparison Tolerance */
    ex_qio,     /* 111 Quad Index Origin */

    ex_run,    /*112 */
    ex_fork,   /*113 */
    ex_wait,   /*114 */
    ex_exec,   /*115 */
    ex_fdef,   /*116 */
    ex_exit,   /*117 */
    ex_pipe,   /*118 */
    ex_chdir,  /*119 */
    ex_open,   /*120 */
    ex_close,  /*121 */
    ex_read,   /*122 */
    ex_write,  /*123 */
    ex_creat,  /*124 */
    ex_seek,   /*125 */
    ex_unlink, /*126 */
    ex_rd,     /*127 */
    ex_dup,    /*128 */
    ex_ap,     /*129 */
    ex_kill,   /*130 */
    ex_crp,    /*131 */
    ex_dfmt,   /*132 */
    ex_mfmt,   /*133 */
    ex_nc,     /*134 */
    ex_nilret, /*135 */
    ex_qlx,    /*136 */
    ex_ibr,    /*137 */
    ex_ibr0,   /*138 */
    ex_botch,  /*139 */
    ex_signl,  /*140 */
    ex_float,  /*141 */
    ex_nl,     /*142 */
    ex_ex,     /*143 added 13.8.1999 by tyl */
    ex_qai,    /*144   	-"-	*/
    ex_qargv,  /*145   	-"-	*/
};
