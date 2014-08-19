;;; apl-mode.el --- mode for editing APL\11 code

;; This edition is for XEmacs

;; Author: Paul Koning <ni1d@arrl.net>
;; Maintainer: Paul Koning <ni1d@arrl.net>
;; Keywords: tools, languages
;; Version: 1.0

;; Copyright (c) 2000 by Paul Koning.

;;; Commentary:

;; This mode was based on asm-mode by Eric S. Raymond <esr@snark.thyrsus.com>

;; This major mode is based on text mode. 

;; This mode runs the usual hook: apl-mode-hook at the end of initialization.

;;; Code:

(defvar apl-mode-syntax-table nil
  "Syntax table used while in Mac mode.")

(defvar apl-mode-font "apl8x13"
  "Font to use for displaying APL code.")

(defvar apl-mode-foreground "white"
  "Foreground color to use for displaying APL code.")

;; set up the default syntax table.
(if apl-mode-syntax-table
    ()
  (setq apl-mode-syntax-table (make-syntax-table))
;  (modify-syntax-entry	?<  "(>" apl-mode-syntax-table)
;  (modify-syntax-entry	?>  ")<" apl-mode-syntax-table)
;  (modify-syntax-entry	?\n ">"  apl-mode-syntax-table)
  )

(defvar apl-mode-abbrev-table nil
  "Abbrev table used while in Mac mode.")
(define-abbrev-table 'apl-mode-abbrev-table ())

(defvar apl-mode-map nil
  "Keymap for Mac mode.")

;; functions to insert the APL characters
;; now if only I could find a way to bind these to characters!
(defun insert-apl-0x80 () (interactive) (insert 128))
(defun insert-apl-0x81 () (interactive) (insert 129))
(defun insert-apl-0x82 () (interactive) (insert 130))
(defun insert-apl-0x83 () (interactive) (insert 131))
(defun insert-apl-0x84 () (interactive) (insert 132))
(defun insert-apl-0x85 () (interactive) (insert 133))
(defun insert-apl-0x86 () (interactive) (insert 134))
(defun insert-apl-0x87 () (interactive) (insert 135))
(defun insert-apl-0x88 () (interactive) (insert 136))
(defun insert-apl-0x89 () (interactive) (insert 137))
(defun insert-apl-0x8a () (interactive) (insert 138))
(defun insert-apl-0x8b () (interactive) (insert 139))
(defun insert-apl-0x8c () (interactive) (insert 140))
(defun insert-apl-0x8d () (interactive) (insert 141))
(defun insert-apl-0x8e () (interactive) (insert 142))
(defun insert-apl-0x8f () (interactive) (insert 143))
(defun insert-apl-0x90 () (interactive) (insert 144))
(defun insert-apl-0x91 () (interactive) (insert 145))
(defun insert-apl-0x92 () (interactive) (insert 146))
(defun insert-apl-0x93 () (interactive) (insert 147))
(defun insert-apl-0x94 () (interactive) (insert 148))
(defun insert-apl-0x95 () (interactive) (insert 149))
(defun insert-apl-0x96 () (interactive) (insert 150))
(defun insert-apl-0x97 () (interactive) (insert 151))
(defun insert-apl-0x98 () (interactive) (insert 152))
(defun insert-apl-0x99 () (interactive) (insert 153))
(defun insert-apl-0x9a () (interactive) (insert 154))
(defun insert-apl-0x9b () (interactive) (insert 155))
(defun insert-apl-0x9c () (interactive) (insert 156))
(defun insert-apl-0x9d () (interactive) (insert 157))
(defun insert-apl-0x9e () (interactive) (insert 158))
(defun insert-apl-0x9f () (interactive) (insert 159))

(if apl-mode-map
    ()
  ;; XEmacs change
  (setq apl-mode-map (make-sparse-keymap 'apl-mode-map))
;;  (setq apl-mode-map (make-keymap))
  (define-key apl-mode-map [unknown-keysym-0x80] 'insert-apl-0x80)
  (define-key apl-mode-map [unknown-keysym-0x81] 'insert-apl-0x81)
  (define-key apl-mode-map [unknown-keysym-0x82] 'insert-apl-0x82)
  (define-key apl-mode-map [unknown-keysym-0x83] 'insert-apl-0x83)
  (define-key apl-mode-map [unknown-keysym-0x84] 'insert-apl-0x84)
  (define-key apl-mode-map [unknown-keysym-0x85] 'insert-apl-0x85)
  (define-key apl-mode-map [unknown-keysym-0x86] 'insert-apl-0x86)
  (define-key apl-mode-map [unknown-keysym-0x87] 'insert-apl-0x87)
  (define-key apl-mode-map [unknown-keysym-0x88] 'insert-apl-0x88)
  (define-key apl-mode-map [unknown-keysym-0x89] 'insert-apl-0x89)
  (define-key apl-mode-map [unknown-keysym-0x8a] 'insert-apl-0x8a)
  (define-key apl-mode-map [unknown-keysym-0x8b] 'insert-apl-0x8b)
  (define-key apl-mode-map [unknown-keysym-0x8c] 'insert-apl-0x8c)
  (define-key apl-mode-map [unknown-keysym-0x8d] 'insert-apl-0x8d)
  (define-key apl-mode-map [unknown-keysym-0x8e] 'insert-apl-0x8e)
  (define-key apl-mode-map [unknown-keysym-0x8f] 'insert-apl-0x8f)
  (define-key apl-mode-map [unknown-keysym-0x90] 'insert-apl-0x90)
  (define-key apl-mode-map [unknown-keysym-0x91] 'insert-apl-0x91)
  (define-key apl-mode-map [unknown-keysym-0x92] 'insert-apl-0x92)
  (define-key apl-mode-map [unknown-keysym-0x93] 'insert-apl-0x93)
  (define-key apl-mode-map [unknown-keysym-0x94] 'insert-apl-0x94)
  (define-key apl-mode-map [unknown-keysym-0x95] 'insert-apl-0x95)
  (define-key apl-mode-map [unknown-keysym-0x96] 'insert-apl-0x96)
  (define-key apl-mode-map [unknown-keysym-0x97] 'insert-apl-0x97)
  (define-key apl-mode-map [unknown-keysym-0x98] 'insert-apl-0x98)
  (define-key apl-mode-map [unknown-keysym-0x99] 'insert-apl-0x99)
  (define-key apl-mode-map [unknown-keysym-0x9a] 'insert-apl-0x9a)
  (define-key apl-mode-map [unknown-keysym-0x9b] 'insert-apl-0x9b)
  (define-key apl-mode-map [unknown-keysym-0x9c] 'insert-apl-0x9c)
  (define-key apl-mode-map [unknown-keysym-0x9d] 'insert-apl-0x9d)
  (define-key apl-mode-map [unknown-keysym-0x9e] 'insert-apl-0x9e)
  (define-key apl-mode-map [unknown-keysym-0x9f] 'insert-apl-0x9f)
  )

(defconst apl-font-lock-keywords
  ()
; '(("^\\(\\(\\sw\\|\\s_\\)+\\):[ \t]*\\(\\sw+\\)?"
;    (1 font-lock-function-name-face) (3 font-lock-keyword-face nil t))
;   ("^\\s +\\(\\(\\sw\\|\\s_\\)+\\)" 1 font-lock-keyword-face))
 "Additional expressions to highlight in APL mode.")

(defconst apl-in-comment-pattern "^[^;]*;")
(defconst apl-inline-empty-comment-pattern "^.+;+ *$")
(defconst apl-flush-left-empty-comment-pattern "^; *$")

(defvar apl-mode-version-string "")

;;;###autoload
(defun apl-mode ()
  "Major mode for editing APL source code.
Features a private abbrev table and the following bindings:

Turning on APL mode runs the hook `apl-mode-hook' at the end of 
initialization.

Special commands:
\\{apl-mode-map}
"
  (interactive)
  (kill-all-local-variables)
  (setq mode-name "APL")
  (setq major-mode 'apl-mode)
  (setq local-abbrev-table apl-mode-abbrev-table)
  (make-local-variable 'font-lock-defaults)
  (setq font-lock-defaults '(apl-font-lock-keywords))
  (make-local-variable 'apl-mode-syntax-table)
  (set-syntax-table apl-mode-syntax-table)
  (setq ctl-arrow 32)
  (use-local-map apl-mode-map)

  ;; XEmacs specific: set font
  (setq sp (face-property 'default 'font))
  (add-spec-to-specifier sp apl-mode-font (current-buffer))
  (if apl-mode-foreground
      (progn
       (setq sp (face-property 'default 'foreground))
       (add-spec-to-specifier sp apl-mode-foreground (current-buffer))
       ))
  (make-local-variable 'comment-start)
  (setq comment-start ";")
  (make-local-variable 'comment-start-skip)
  (setq comment-start-skip ";+[ \t]*")
  (make-local-variable 'comment-end)
  (setq comment-end "")

  (run-hooks 'apl-mode-hook))

(defun apl-pop-comment-level ()
  ;; Delete an empty comment ending current line.  Then set up for a new one,
  ;; on the current line if it was all comment, otherwise above it
  (end-of-line)
  (delete-horizontal-space)
  (while (= (preceding-char) ?\;)
    (delete-backward-char 1))
  (delete-horizontal-space)
  (if (bolp)
      ()
    (beginning-of-line)
    (open-line 1))
  )


(defun apl-comment ()
  "Convert an empty comment to a `larger' kind, or start a new one.
These are the known comment classes:

   1 -- comment to the right of the code (at the comment-column)
   2 -- comment on its own line, beginning at the left-most column.

Suggested usage:  while writing your code, trigger apl-comment
repeatedly until you are satisfied with the kind of comment."
  (interactive)
  (cond

   ;; Blank line?  Then start comment at left margin.
   ((apl-line-matches "^[ \t]*$")
    (delete-horizontal-space)
    (insert comment-start " "))

   ;; Nonblank line with no comment chars in it?
   ;; Then start a comment at the current comment column
   ((not (apl-insert-literal-p))
    (indent-to-column comment-column)
    (insert ";")
    (end-of-line))

   ;; If all else fails, insert character
   (t
    (insert ";"))

   ))

;;; apl-mode.el ends here
