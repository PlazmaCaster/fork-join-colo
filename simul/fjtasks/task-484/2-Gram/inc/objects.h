#ifndef __OBJECTS_H__
#define __OBJECTS_H__

/**
 * @file objects.h
 *
 * Declares the objects used in the fork-join task
 */

/**
 * @define objpart(n)
 *
 * Declare that the function is part of an object
 * By example, this places the function bar() in the 3rd object:
 

 void objpart(3) bar(int n) {
    int sq = foo(n);
 }

 * Note, that foo() is being called from within bar(), therefore it
 * must also be part of the object:

 int objpart(3) foo(int n) { return n * n; }
 */
#define object(n) \
	__attribute__((__section__(".object"#n)))

typedef void (object_t)(void);

void object01();
void object02();
void object03();
void object04();
void object05();
void object06();
void object07();
void object08();
void object09();
void object10();
void object11();
void object12();
void object13();
void object14();
void object15();
void object16();
void object17();
void object18();
#endif /* __OBJECTS_H__ */
