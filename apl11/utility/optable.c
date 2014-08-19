/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

/*
 * Declarations of all functions (required by Version 7 C
 * for the array to be set up without warning messages)
 */

	extern ex_abs();
	extern ex_add();
	extern ex_and();
	extern ex_ap();
	extern ex_arg1();
	extern ex_arg2();
	extern ex_asgn();
	extern ex_auto();
	extern ex_base();
	extern ex_botch();
	extern ex_br();
	extern ex_br0();
	extern ex_cat();
	extern ex_catk();
	extern ex_ceil();
	extern ex_chdir();
	extern ex_cir();
	extern ex_close();
	extern ex_com();
	extern ex_com0();
	extern ex_comb();
	extern ex_comk();
	extern ex_creat();
	extern ex_crp();
	extern ex_ddom();
	extern ex_deal();
	extern ex_dfmt();
	extern ex_dibm();
	extern ex_diot();
	extern ex_div();
	extern ex_drho();
	extern ex_drop();
	extern ex_dtrn();
	extern ex_dup();
	extern ex_elid();
	extern ex_eps();
	extern ex_eq();
	extern ex_exd();
	extern ex_exd0();
	extern ex_exdk();
	extern ex_exec();
	extern ex_exit();
	extern ex_exp();
	extern ex_fac();
	extern ex_fdef();
	extern ex_float();
	extern ex_nl();
	extern ex_floor();
	extern ex_fork();
	extern ex_fun();
	extern ex_gdd();
	extern ex_gddk();
	extern ex_gdu();
	extern ex_gduk();
	extern ex_ge();
	extern ex_gt();
	extern ex_hprint();
	extern ex_ibr();
	extern ex_ibr0();
	extern ex_syscom();
	extern ex_index();
	extern ex_iprod();
	extern ex_kill();
	extern ex_label();
	extern ex_le();
	extern ex_log();
	extern ex_loge();
	extern ex_lt();
	extern ex_max();
	extern ex_mdom();
	extern ex_menc();
	extern ex_execute();
	extern ex_mfmt();
	extern ex_mibm();
	extern ex_min();
	extern ex_minus();
	extern ex_miot();
	extern ex_mod();
	extern ex_mrho();
	extern ex_mtrn();
	extern ex_mul();
	extern ex_nand();
	extern ex_nc();
	extern ex_ne();
	extern ex_nilret();
	extern ex_nor();
	extern ex_not();
	extern ex_open();
	extern ex_oprod();
	extern ex_or();
	extern ex_pi();
	extern ex_pipe();
	extern ex_plus();
	extern ex_print();
	extern ex_pwr();
	extern ex_quad();
	extern ex_qquad();
	extern	ex_qav();
	extern	ex_qct();
	extern	ex_qio();
	extern	ex_qlx();
	extern	ex_qpp();
	extern	ex_qpw();
	extern	ex_qts();
	extern ex_rand();
	extern ex_rav();
	extern ex_ravk();
	extern ex_rd();
	extern ex_read();
	extern ex_recip();
	extern ex_red();
	extern ex_red0();
	extern ex_redk();
	extern ex_rep();
	extern ex_rest();
	extern ex_rev();
	extern ex_rev0();
	extern ex_revk();
	extern ex_rot();
	extern ex_rot0();
	extern ex_rotk();
	extern ex_run();
	extern ex_scan();
	extern ex_scn0();
	extern ex_scnk();
	extern ex_seek();
	extern ex_sgn();
	extern ex_signl();
	extern ex_sub();
	extern ex_take();
	extern ex_unlink();
	extern ex_wait();
	extern ex_write();
	extern ex_ex();
	extern ex_qai();

/* WARNING, the following must agree with opt_codes.h and code_dump.c */
int (*exop[])() = {

	0, 		/* 0 */
	0,		/* 1 */
	ex_add, 	/* 2 */
	ex_plus, 	/* 3 */
	ex_sub, 	/* 4 */
	ex_minus, 	/* 5 */
	ex_mul, 	/* 6 */
	ex_sgn, 	/* 7 */
	ex_div, 	/* 8 */
	ex_recip, 	/* 9 */
	ex_mod, 	/* 10 */
	ex_abs, 	/* 11 */
	ex_min, 	/* 12 */
	ex_floor, 	/* 13 */
	ex_max, 	/* 14 */
	ex_ceil, 	/* 15 */
	ex_pwr, 	/* 16 */
	ex_exp, 	/* 17 */
	ex_log, 	/* 18 */
	ex_loge, 	/* 19 */
	ex_cir, 	/* 20 */
	ex_pi, 		/* 21 */
	ex_comb, 	/* 22 */
	ex_fac, 	/* 23 */
	ex_deal, 	/* 24 */
	ex_rand, 	/* 25 */
	ex_drho, 	/* 26 */
	ex_mrho, 	/* 27 */
	ex_diot, 	/* 28 */
	ex_miot, 	/* 29 */
	ex_rot0, 	/* 30 */
	ex_rev0, 	/* 31 */
	ex_dtrn, 	/* 32 */
	ex_mtrn, 	/* 33 */
	ex_dibm, 	/* 34 */
	ex_mibm, 	/* 35 */
	ex_gdu, 	/* 36 */
	ex_gduk, 	/* 37 */
	ex_gdd, 	/* 38 */
	ex_gddk, 	/* 39 */
	ex_exd, 	/* 40 */
	ex_scan, 	/* 41 */
	ex_exdk, 	/* 42 */
	ex_scnk, 	/* 43 */
	ex_iprod, 	/* 44 */
	ex_oprod, 	/* 45 */
	ex_quad, 	/* 46 */
	ex_qquad, 	/* 47 */
	ex_br0, 	/* 48 */
	ex_br, 		/* 49 */
	ex_ddom, 	/* 50 */
	ex_mdom, 	/* 51 */
	ex_com, 	/* 52 */
	ex_red, 	/* 53 */
	ex_comk, 	/* 54 */
	ex_redk, 	/* 55 */
	ex_rot, 	/* 56 */
	ex_rev, 	/* 57 */
	ex_rotk, 	/* 58 */
	ex_revk, 	/* 59 */
	ex_cat, 	/* 60 */
	ex_rav, 	/* 61 */
	ex_catk, 	/* 62 */
	ex_ravk, 	/* 63 */
	ex_print, 	/* 64 */
	0, 		/* 65 */
	ex_elid, 	/* 66 */
	0, 		/* 67 */
	0, 		/* 68 */
	ex_index, 	/* 69 */
	ex_hprint, 	/* 70 */
	ex_lt, 		/* 71 */
	ex_le, 		/* 72 */
	ex_gt, 		/* 73 */
	ex_ge, 		/* 74 */
	ex_eq, 		/* 75 */
	ex_ne, 		/* 76 */
	ex_and, 	/* 77 */
	ex_or, 		/* 78 */
	ex_nand, 	/* 79 */
	ex_nor, 	/* 80 */
	ex_not, 	/* 81 */
	ex_eps, 	/* 82 */
	ex_execute, 	/* 83 */
	ex_rep, 	/* 84 */
	ex_take, 	/* 85 */
	ex_drop, 	/* 86 */
	ex_exd0, 	/* 87 */
	ex_asgn, 	/* 88 */
	ex_syscom, 	/* 89 */
	0, 		/* 90 */
	0, 		/* 91 */
	ex_fun, 	/* 92 */
	ex_arg1, 	/* 93 */
	ex_arg2, 	/* 94 */
	ex_auto, 	/* 95 */
	ex_rest, 	/* 96 */
	ex_com0, 	/* 97 */
	ex_red0, 	/* 98 */
	ex_exd0, 	/* 99 */
	ex_scn0, 	/*100 */
	ex_base, 	/*101 */
	ex_menc, 	/*102			monadic encod   */
	ex_label, 	/*103 */
	0, 		/*104 */
	ex_qlx,		/* 105 Quad Latent eXpression */
	ex_qav,		/* 106 Quad Atomic Vector */
	ex_qts,		/* 107 Quad Time Stamp */
	ex_qpp,		/* 108 Quad Print Precision */
	ex_qpw,		/* 109 Quad Print Width */
	ex_qct,		/* 110 Quad Comparison Tolerance */
	ex_qio,		/* 111 Quad Index Origin */

	ex_run, 	/*112 */
	ex_fork, 	/*113 */
	ex_wait, 	/*114 */
	ex_exec, 	/*115 */
	ex_fdef, 	/*116 */
	ex_exit, 	/*117 */
	ex_pipe, 	/*118 */
	ex_chdir, 	/*119 */
	ex_open, 	/*120 */
	ex_close, 	/*121 */
	ex_read, 	/*122 */
	ex_write, 	/*123 */
	ex_creat, 	/*124 */
	ex_seek, 	/*125 */
	ex_unlink, 	/*126 */
	ex_rd, 		/*127 */
	ex_dup, 	/*128 */
	ex_ap, 		/*129 */
	ex_kill, 	/*130 */
	ex_crp, 	/*131 */
	ex_dfmt, 	/*132 */
	ex_mfmt, 	/*133 */
	ex_nc, 		/*134 */
	ex_nilret, 	/*135 */
	ex_qlx, 	/*136 */
	ex_ibr, 	/*137 */
	ex_ibr0, 	/*138 */
	ex_botch, 	/*139 */
	ex_signl, 	/*140 */
	ex_float, 	/*141 */
	ex_nl,		/*142 */
	ex_ex,		/*143 added 13.8.1999 by tyl */
	ex_qai,		/*144   	-"-	*/
};
