/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

/*
 * Declarations of all functions (required by Version 7 C
 * for the array to be set up without warning messages)
 */

	extern void ex_abs();
	extern void ex_add();
	extern void ex_and();
	extern void ex_ap();
	extern void ex_arg1();
	extern void ex_arg2();
	extern void ex_asgn();
	extern void ex_auto();
	extern void ex_base();
	extern void ex_botch();
	extern void ex_br();
	extern void ex_br0();
	extern void ex_cat();
	extern void ex_catk();
	extern void ex_ceil();
	extern void ex_chdir();
	extern void ex_cir();
	extern void ex_close();
	extern void ex_com();
	extern void ex_com0();
	extern void ex_comb();
	extern void ex_comk();
	extern void ex_creat();
	extern void ex_crp();
	extern void ex_ddom();
	extern void ex_deal();
	extern void ex_dfmt();
	extern void ex_dibm();
	extern void ex_diot();
	extern void ex_div();
	extern void ex_drho();
	extern void ex_drop();
	extern void ex_dtrn();
	extern void ex_dup();
	extern void ex_elid();
	extern void ex_eps();
	extern void ex_eq();
	extern void ex_exd();
	extern void ex_exd0();
	extern void ex_exdk();
	extern void ex_exec();
	extern void ex_exit();
	extern void ex_exp();
	extern void ex_fac();
	extern void ex_fdef();
	extern void ex_float();
	extern void ex_nl();
	extern void ex_floor();
	extern void ex_fork();
	extern void ex_fun();
	extern void ex_gdd();
	extern void ex_gddk();
	extern void ex_gdu();
	extern void ex_gduk();
	extern void ex_ge();
	extern void ex_gt();
	extern void ex_hprint();
	extern void ex_ibr();
	extern void ex_ibr0();
	extern void ex_syscom();
	extern void ex_index();
	extern void ex_iprod();
	extern void ex_kill();
	extern void ex_label();
	extern void ex_le();
	extern void ex_log();
	extern void ex_loge();
	extern void ex_lt();
	extern void ex_max();
	extern void ex_mdom();
	extern void ex_menc();
	extern void ex_execute();
	extern void ex_mfmt();
	extern void ex_mibm();
	extern void ex_min();
	extern void ex_minus();
	extern void ex_miot();
	extern void ex_mod();
	extern void ex_mrho();
	extern void ex_mtrn();
	extern void ex_mul();
	extern void ex_nand();
	extern void ex_nc();
	extern void ex_ne();
	extern void ex_nilret();
	extern void ex_nor();
	extern void ex_not();
	extern void ex_open();
	extern void ex_oprod();
	extern void ex_or();
	extern void ex_pi();
	extern void ex_pipe();
	extern void ex_plus();
	extern void ex_print();
	extern void ex_pwr();
	extern void ex_quad();
	extern void ex_qquad();
	extern void	ex_qav();
	extern void	ex_qct();
	extern void	ex_qio();
	extern void	ex_qlx();
	extern void	ex_qpp();
	extern void	ex_qpw();
	extern void	ex_qts();
	extern void ex_rand();
	extern void ex_rav();
	extern void ex_ravk();
	extern void ex_rd();
	extern void ex_read();
	extern void ex_recip();
	extern void ex_red();
	extern void ex_red0();
	extern void ex_redk();
	extern void ex_rep();
	extern void ex_rest();
	extern void ex_rev();
	extern void ex_rev0();
	extern void ex_revk();
	extern void ex_rot();
	extern void ex_rot0();
	extern void ex_rotk();
	extern void ex_run();
	extern void ex_scan();
	extern void ex_scn0();
	extern void ex_scnk();
	extern void ex_seek();
	extern void ex_sgn();
	extern void ex_signl();
	extern void ex_sub();
	extern void ex_take();
	extern void ex_unlink();
	extern void ex_wait();
	extern void ex_write();
	extern void ex_ex();
	extern void ex_qai();

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
