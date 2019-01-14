#!/usr/bin/scheme --script

(define (fact n) 
	(if (= 0 n)
			1
			(* n (fact (- n 1)))))

(define (do-each-line f) 
	(let ((l (read)))
		(unless (eof-object? l)
				(begin (display l)
							 (display "!")
							 (newline) 
							 (f l)
							 (do-each-line f)))
	 ))

(define (write-fact-ln n)
	(begin
		(display (fact n))
		(newline)
))

(do-each-line write-fact-ln)
