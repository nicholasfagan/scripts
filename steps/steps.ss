;removes the last element in a list.
(define (rm-last lst) 
	(if (or (null? lst) (null? (cdr lst)))
			'()
			(cons (car lst) (rm-last (cdr lst)))))




(define (fibn curr end prev)
	(if(>= (+ 1 curr) end)
		(car prev)
		(fibn (+ 1 curr) end (cons (fold-left + 0 prev) (rm-last prev)))))
