#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct node; typedef struct node {char *s; struct node *next;} node;
node *add_to_front(char *s, node *old) {
		node *new = malloc(sizeof(node)); if(new == NULL) exit(1);
		(*new) = (node){.s=s,.next=old};
		return new;
}
node *insert(node *head, char *s) {
	if(head == NULL || strcmp(head->s, s) > 0) head = add_to_front(s,head);
	else if(head->next == NULL || strcmp(head->next->s, s) > 0) head->next = add_to_front(s,head->next);
	else head->next = insert(head->next, s);
	return head;
}
void del(node *n) {
	if(n==NULL)return;
	free(n->s);n->s=NULL;
	del(n->next);n->next=NULL;
	free(n);n=NULL;
}
void print(node *n) {
	if(n == NULL) return;
	printf("%s\n",n->s);
	print(n->next);
}
char *read_cl() {
	int cap = 64, len = 0, c, pc = 0;
	char *buf = malloc(cap*sizeof(char)); if(buf == NULL) return NULL;
	while((c = getchar()) != EOF && !(c == '\n' && pc != '\\')) {
		if(cap<=len+2) buf = realloc(buf, (cap *= 2) * sizeof(char)); if(buf == NULL) return NULL;
		pc = buf[len++] = c;
	}buf[len] = 0;
	if(c==EOF&&len==0){free(buf);buf=NULL;}
	return buf;
}
int main(void) {
	char *buf;node *head = NULL;
	while((buf = read_cl()) != NULL) head = insert(head, buf);
	print(head);del(head);
	return 0;
}
