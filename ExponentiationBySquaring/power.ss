#!/usr/bin/scheme --script

(define (even a) (= 0 (modulo a 2)))
;fast power, using exponentiation by squaring
(define (fpow a b) 
	(
	 if (= b 0)
			1
			(
			 if (even b)
			 (fpow (* a a) (/ b 2))
			 (* a (fpow a (- b 1)))
			)
	)
)

; slow traditional approach
(define (spow a b) 
	(if (= b 0)
			1
			(* a (spow a (- b 1)))))

