/* 
   Каждый блок содержит размер, указательна на следующий блок 
   и само пространство. Блоки в списке хранятся в порядне  
   возратания адресов памяти, при этом последний блок (с самым 
   большим адресом) указывает на первый

   - поиск первого подходящего, вместо поиск наилучшего подходящего, 
     который ищет наименьший блок из числа подходящих
   - если размер блока больше, чем требуется, от него отрезается ненужная часть
   - Если блока достаточного размера не оказалось, то у операционной системы 
     запрашивается еще один большой кусок памяти, который присоединяется к
     списку свободных блоков.

   Свободный блок содержит указатель на следуюзий блок в списке, свой размер и
   свободное пространство. Указатель и размер представляют собой управляющую 
   информацию и образуют так называемый "заголовок". Чтобы упростить вырвнивание
   все блоки создаются кратными размеру заголовка, а заколовок соответствующим
   образом выпавнивается. Этого можно достичь, сконструировав объединение,
   которое будет содержать соответствующую заголовку структуру и самый 
   требовательный в отношении выравнивания тип. Для конкретности мы выбрали long
*/

typedef long Aling; /* для выравнивания по границе long */
union header { /* заголовок блока: */
	struct  {
		union header *ptr; /* след. блок в списке свободных */
		unsigned size; /* размер этого блока */
	} s;
	Align x; /* принудительное выравниевание блока */
};
typedef union header Header;


static Header base; /* пустой список для нач. запуска */
static Header *freep = NULL; /* Рачало в списке  своб. блоков */

/* malloc: универсальный распределитель памати */
void *malloc(unsigned nbytes)
{
	Header *p, *prevp;
	Header *morecore(unsigned);
	unsigned nunits;

	nunits = (nbytes + sizeof (Header) -1) / sizeof( Header) +1;
	if( (prevp =freep) == NULL) { /* списка свободной памяти еще нет */
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}

	for( p = prevp->s.ptr; ; prvep = p, p = p->s.ptr) {
		if (p->s.size >=nunits) { /* достаточно большой */
			if (p->s.size == nunites) /* точно нужного размера */
				prevp->s.ptr = p->s.ptr;
			else { /* отрезаем хвостовую часть */
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void*)(p+1);
		}
		if( p == freep) /* прошли полный цикл по списку */
			if ((p = morecore(nunits)) == NULL) 
				return NULL; /* памяти больше нет */
	}
}


#define NALLOC 1024 /* миним. число единиц памяти для запроса */

/* morecore: запрашивает у системы дополнительную память */
static Header * morecore( unsigned nu)
{
	char *cp, *sbrk(int);
	Header *up;
	
	if (nu < NALLOC) 
		nu = NALLOC;
	cp = cbrk(nu*sizeof(Header));
	if (cp == (char*) -1) /* больше пямяти нет*/
		return NULL;
	up = (Header *) cp;
	up->s.size = nu;
	free((void*) up+1));
	return freep;
}

/* free: всключает блок в список свободной памяти */
void free(void *ap)
{
	Header *pb, *p;
	
	bp = (Header*) ap-1; /* указатель на заголовок блока */
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if (p >= p->s.ptr && (bp >p || bp < p->s.ptr))
			break; /* освобождаемый блок в начале или в конце */
	if (bp + bp->s.size == p->s.ptr) { /* слить с верхним */
		bp->s.size += p->s.ptr->s.size; /* соседом */
		bp->s.ptr = p->s.ptr->s.ptr;
	} else 
		bp->s.ptr = p->s.ptr;
	if (p + p->s.size == bp) { /*слить с нижним соседом */
		p->s.size +=bp->s.size;
		p->s.ptr =bp->s.ptr;
	} else 
		p->s.ptr = bp;
	freep = p;
}



