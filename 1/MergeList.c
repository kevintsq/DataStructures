LinkList Mergelist(LinkList lista, LinkList listb)
{
    LinkList listc, p = lista, q = listb, r;
    if(lista->data <= listb->data){
        listc = lista;
        r = lista;
        p = lista->link;
    }else{
        listc = listb;
        r = listb;
        q = listb->link;
    }
    while(p!=NULL&&q!=NULL){
        if(p->data <= q->data){
            r->link = p;
            r = p;
            p = p->link;
        }else{
            r->link = q;
            r = q;
            q = q->link;
        }
    }
    r->link = q == NULL ? p : q;
    return listc;
}