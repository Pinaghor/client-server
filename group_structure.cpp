/*#include <cstdio>
#include <cstring>
#include <cstdlib>*/





#include "frog.h"



thirdnode::thirdnode(char *name, int phone, int group) {
    if(name) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }
    this->phone = phone;
    this->group = group;
    leftg = 0;
    rightg = 0;
    equalg = 0;
    parentg = 0;
    //prevn = 0;
    //nextn = 0;
    color = BLACK;
}
thirdnode::~thirdnode() {
    leftg = 0;
    rightg = 0;
    equalg = 0;
    parentg = 0;
    //prevn = 0;
    //nextn = 0;
}
/*
thirdnode* thirdnode::uncle() {
	if(this->parentg) {
		if(this->parentg->parentg) {
			if(this->parentg->parentg->leftg == this->parentg) {
				return this->parentg->parentg->rightg;
			}
			return this->parentg->parentg->leftg;
		}
	}
	return 0;
}
thirdnode* thirdnode::brother() {
	if(this->parentg) {
		if(this->parentg->leftg == this)
		return this->parentg->rightg;
		return this->parentg->leftg;
	}
	return 0;
}*/
int thirdnode::operator>(thirdnode & b) {
	if(this->group > b.group)
        return 1;
	return 0;
}
int thirdnode::operator<(thirdnode & b) {
    if(this->group < b.group)
        return 1;
    return 0;
}
int thirdnode::operator>=(thirdnode & b) {
	if(this->group >= b.group)
return 1;
	return 0;
}
int thirdnode::operator<=(thirdnode & b) {
	if(this->group <= b.group)
	return 1;
	return 0;
}
int thirdnode::operator==(thirdnode & b) {
	if(this->group == b.group)
	return 1;
	return 0;
}
int thirdnode::operator!=(thirdnode & b) {
	if(this->group != b.group)
	return 1;
	return 0;
}
int cmp(int a, int b) {
    if(a > b) {
        return 1;
    }
    if(a < b) {
        return -1;
    }
    return 0;
}

    group_structure::group_structure() {
        head = 0;
        curr = 0;
        nil = new thirdnode();
        head = nil;
    }
    void group_structure::make_head(thirdnode *node) {
        if(!node) {
            return;
        }
        while(node->parentg != nil)node = node->parentg;
        head = node;
    }




void group_structure::add_node(thirdnode* new_thirdnode)
{
    thirdnode *mem, *runner;
    int res;

    mem = nil;
    runner = head;
    while (runner != nil)
    {
        mem = runner;
        res = cmp (new_thirdnode->group, runner->group);
        if (res < 0) runner = runner->leftg;
        if (res > 0) runner = runner->rightg;
        if (res == 0)
        {
            new_thirdnode->equalg = runner->equalg;
            runner->equalg = new_thirdnode;
            new_thirdnode->color = runner->color;
            return;
        }
    }
    new_thirdnode->parentg = mem;
    if (mem == nil) head = new_thirdnode;
    else 
    {
        res = cmp (new_thirdnode->group, mem->group);
        if (res < 0) mem->leftg = new_thirdnode;
        if (res > 0) mem->rightg = new_thirdnode;
        if (res == 0) printf ("PANIC SHOULD HAPPEN BAD ADD\n");
    }
    new_thirdnode->leftg = new_thirdnode->rightg = nil;
    new_thirdnode->color = RED;
    repair_inc (new_thirdnode);
}
void group_structure::repair_inc (thirdnode* new_thirdnode)
{
    thirdnode* mem;

    while (new_thirdnode->parentg->color == RED)
    {
        if (new_thirdnode->parentg == new_thirdnode->parentg->parentg->leftg)
        {
            mem = new_thirdnode->parentg->parentg->rightg;
            if (mem->color == RED)
            {
                new_thirdnode->parentg->color = BLACK;
                mem->color = BLACK;
                new_thirdnode->parentg->parentg->color = RED;
                new_thirdnode = new_thirdnode->parentg->parentg;
            }
            else 
            {
                if (new_thirdnode == new_thirdnode->parentg->rightg)
                {
                    new_thirdnode = new_thirdnode->parentg;
                    left_roll (new_thirdnode);
                }
                new_thirdnode->parentg->color = BLACK;
                new_thirdnode->parentg->parentg->color = RED;
                right_roll (new_thirdnode->parentg->parentg);
            }
        }
        else
        {
            mem = new_thirdnode->parentg->parentg->leftg;
            if (mem->color == RED)
            {
                new_thirdnode->parentg->color = BLACK;
                mem->color = BLACK;
                new_thirdnode->parentg->parentg->color = RED;
                new_thirdnode = new_thirdnode->parentg->parentg;
            }
            else 
            {
                if (new_thirdnode == new_thirdnode->parentg->leftg)
                {
                    new_thirdnode = new_thirdnode->parentg;
                    right_roll (new_thirdnode);
                }
                new_thirdnode->parentg->color = BLACK;
                new_thirdnode->parentg->parentg->color = RED;
                left_roll (new_thirdnode->parentg->parentg);
            }
        }
    }
    head->color = BLACK;
}


thirdnode* group_structure::del_node (thirdnode* rmnode)
{
    thirdnode *mem1, *mem2;
    int oldcolor;

    if (rmnode->equalg)
    {
        mem1 = rmnode->equalg;
        if (rmnode->parentg == nil) head = mem1;
        else if (rmnode == rmnode->parentg->leftg) rmnode->parentg->leftg = mem1;
        else rmnode->parentg->rightg = mem1;
        mem1->leftg = rmnode->leftg;
        mem1->rightg = rmnode->rightg;
        mem1->parentg = rmnode->parentg;
        mem1->color = rmnode->color;
        if (rmnode->leftg != nil) rmnode->leftg->parentg = mem1;
        if (rmnode->rightg != nil) rmnode->rightg->parentg = mem1;
    }
    else
    {
        mem1 = rmnode;
        oldcolor = mem1->color;
        if (rmnode->leftg == nil)
        {
            mem2 = rmnode->rightg;
            replace_subtree (rmnode, rmnode->rightg);
        }
        else
        {
            if (rmnode->rightg == nil)
            {
                mem2 = rmnode->leftg;
                replace_subtree (rmnode, rmnode->leftg);
            }
            else
            {
                mem1 = rmnode->rightg;
                while (mem1->leftg != nil) mem1 = mem1->leftg;
                oldcolor = mem1->color;
                mem2 = mem1->rightg;
                if (mem1->parentg == rmnode) mem2->parentg = mem1;
                else 
                {
                    replace_subtree (mem1, mem1->rightg);
                    mem1->rightg = rmnode->rightg;
                    mem1->rightg->parentg = mem1;
                }
                replace_subtree (rmnode, mem1);
                mem1->leftg = rmnode->leftg;
                mem1->leftg->parentg = mem1;
                mem1->color = rmnode->color;
            }
        }
        if (oldcolor == BLACK) repair_del (mem2);
    }
    return rmnode;
}

void group_structure::replace_subtree (thirdnode *a, thirdnode *b)
{
    if (a->parentg == nil) head = b;
    else if (a == a->parentg->leftg) a->parentg->leftg = b;
    else a->parentg->rightg = b;
    b->parentg = a->parentg;
}
void group_structure::repair_del (thirdnode* subst)
{
    thirdnode *mem;

    while (subst != head && subst->color == BLACK)
    {
        if (subst == subst->parentg->leftg)
        {
            mem = subst->parentg->rightg;
            if (mem->color == RED)
            {
                mem->color = BLACK;
                subst->parentg->color = RED;
                left_roll (subst->parentg);
                mem = subst->parentg->rightg;
            }
            if (mem->leftg->color == BLACK && mem->rightg->color == BLACK)
            {
                mem->color = RED;
                subst = subst->parentg;
            }
            else 
            {
                if (mem->rightg->color == BLACK)
                {
                    mem->leftg->color = BLACK;
                    mem->color = RED;
                    right_roll (mem);
                    mem = subst->parentg->rightg;
                }
                mem->color = subst->parentg->color;
                subst->parentg->color = BLACK;
                mem->rightg->color = BLACK;
                left_roll (subst->parentg);
                subst = head;
            }
        }
        else
        {
            mem = subst->parentg->leftg;
            if (mem->color == RED)
            {
                mem->color = BLACK;
                subst->parentg->color = RED;
                right_roll (subst->parentg);
                mem = subst->parentg->leftg;
            }
    if (mem->rightg->color == BLACK && mem->leftg->color == BLACK)
            {
                mem->color = RED;
                subst = subst->parentg;
            }
            else 
            {
                if (mem->leftg->color == BLACK)
                {
                    mem->rightg->color = BLACK;
                    mem->color = RED;
                    left_roll (mem);
                    mem = subst->parentg->leftg;
                }
                mem->color = subst->parentg->color;
                subst->parentg->color = BLACK;
                mem->leftg->color = BLACK;
                right_roll (subst->parentg);
                subst = head;
            }
        }
    }
    subst->color = BLACK;
}

thirdnode* group_structure::check_for_null() {
    thirdnode* prev;
    thirdnode* curr;
    prev = nil;
    curr = head;
    while(curr != nil) {
        if(curr->leftg == 0 || curr->rightg == 0 || curr->parentg == 0 || curr->group == 0 || curr->phone == 0 || curr->name == 0) {
            return curr;
        }
        if(curr->parentg == prev) {
            if(curr->leftg != nil) {
                prev = curr;
                curr = curr->leftg;
                continue;
            }
            if(curr->rightg != nil) {
                prev = curr;
                curr = curr->rightg;
                continue;
            }
            prev = curr;
            curr = curr->parentg;
            continue;
        }
        if(curr->leftg == prev) {
            if(curr->rightg != nil) {
                prev = curr;
                curr = curr->rightg;
                continue;
            }
            prev = curr;
            curr = curr->parentg;
            continue;
        }
        if(curr->rightg == prev) {
            prev = curr;
            curr = curr->parentg;
            continue;
        }
    }
    return 0;
}






    thirdnode* group_structure::find_node(int g, cond_type c_type) {
    	if(head == nil){return 0;}
    	curr = head;
        while(curr) {
    		if(curr->group == g) {
    			return curr;
    		}
    		if(g < curr->group) {
                if(c_type == GE || c_type == GT) {
                    return curr;
                }
                if(curr->leftg && curr->leftg != nil) {
    				curr = curr->leftg;
    				continue;
    			}
    			return 0;
    		}
            if(c_type == LE || c_type == LT) {
                return curr;
            }
            if(curr->rightg && curr->rightg != nil) {
    			curr = curr->rightg;
    			continue;
    		}
    		return 0;
    	}
    	return 0;
    }
    void group_structure::fprint(FILE* fp, int i, thirdnode *curr) {
    	int j;
    	char color[3];
    	if(curr == 0){
    		curr = head;
    	}
    	if(head == nil) {
    		fprintf(fp, "Empty tree\n");
            return;
    	}
    	if(curr->color == RED) {
    		strcpy(color, "R\0");
    	}
    	else {
    		strcpy(color, "B\0");
    	}
    	if( MAX_DEEP_IN_TREE_PRINT - i > 0) {
    		if(curr->rightg != nil) {
    			this->fprint(fp, i + 1, curr->rightg);
    		}
            if(curr->rightg && curr->rightg != nil && curr->rightg->parentg && curr->rightg->parentg != curr) {// BREAK IT 2
                for(j = 0; j < i; j++)
                fprintf(fp, "\t|");
                fprintf(fp, "R%d||\n", curr->rightg->parentg->group);
            }
    		for(j = 0; j < i; j++)
    		fprintf(fp, "\t|");

    		fprintf(fp, "%d %s-----|\n", curr->group, color);
            if(curr->leftg && curr->leftg != nil && curr->leftg->parentg != curr) {// BREAK IT
                for(j = 0; j < i; j++)
                fprintf(fp, "\t|");
                fprintf(fp, "L%d||", curr->leftg->parentg->group);
            }
    		fprintf(fp, "\n");
    		if(curr->leftg != nil) {
    			this->fprint(fp, i + 1, curr->leftg);
    		}
    	}
    	return;
    }

/*void left_roll(thirdnode* bad_node) {
    thirdnode* another;

    another = bad_node->rightg


	thirdnode* another;
	another = bad_node->rightg;
	another->parentg = bad_node->parentg;
	if(bad_node->parentg != 0) {
		if(bad_node->parentg->leftg == bad_node) {
			bad_node->parentg->leftg = another;
		}
		else {
			bad_node->parentg->rightg = another;
		}
	}
	bad_node->rightg = another->leftg;
	if(another->leftg != 0) {
		another->leftg->parentg = bad_node;
	}
	bad_node->parentg = another;
	another->leftg = bad_node;
} */

void group_structure::left_roll (thirdnode* bad_node)
{
    thirdnode* another;

    another = bad_node->rightg;
    bad_node->rightg = another->leftg;
    if (another->leftg != nil) another->leftg->parentg = bad_node;
    another->parentg = bad_node->parentg;
    if (bad_node->parentg == nil) head = another;
    else if (bad_node == bad_node->parentg->rightg) bad_node->parentg->rightg = another;
    else bad_node->parentg->leftg = another;
    another->leftg = bad_node;
    bad_node->parentg = another;
}


/*void right_roll(thirdnode* bad_node) {
	thirdnode* another;
	another = bad_node->leftg;
	another->parentg = bad_node->parentg;
	if(bad_node->parentg != 0) {
		if(bad_node->parentg->leftg == bad_node) {
			bad_node->parentg->leftg = another;
		}
		else {
			bad_node->parentg->rightg = another;
		}
	}
	bad_node->leftg = another->rightg;
	if(another->rightg != 0) {
		another->rightg->parentg = bad_node;
	}
	bad_node->parentg = another;
	another->rightg = bad_node;
} */

void group_structure::right_roll(thirdnode* bad_node) {
    thirdnode* another;

    another = bad_node->leftg;
    bad_node->leftg = another->rightg;
    if (another->rightg != nil) another->rightg->parentg = bad_node;
    another->parentg = bad_node->parentg;
    if (bad_node->parentg == nil) head = another;
    else if (bad_node == bad_node->parentg->leftg) bad_node->parentg->leftg = another;
    else bad_node->parentg->rightg = another;
    another->rightg = bad_node;
    bad_node->parentg = another;
}


/*void swap(thirdnode *a, thirdnode *b) {
    thirdnode just_node;

    //------------------------------  1.
    just_node.parentg = a->parentg;
    a->parentg = b->parentg;
    b->parentg = just_node.parentg;
    just_node.leftg = a->leftg;
    a->leftg = b->leftg;
    b->leftg = just_node.leftg;
    just_node.rightg = a->rightg;
    a->rightg = b->rightg;
    b->rightg = just_node.rightg;
    just_node.color = a->color;
    a->color = b->color;
    b->color = just_node.color;
    //--------------------------  2.
    if(a->parentg == a) {
        a->parentg = b;
    }
    if(a->leftg == a) {
        a->leftg = b;
    }
    if(a->rightg == a) {
        a->rightg = b;
    }
    if(b->parentg == b) {
        b->parentg = a;
    }
    if(b->leftg == b) {
        b->leftg = a;
    }
    if(b->rightg == b) {
        b->rightg = a;
    }
    //-------------------------------  3)
    if(a->parentg != nil) {
        if(a->parentg->leftg == b || a->parentg->leftg == a) {
            a->parentg->leftg = a;
        }
        else {
            a->parentg->rightg = a;
        }
    }
    if(a->leftg != nil) {
        a->leftg->parentg = a;
    }
    if(a->rightg != nil) {
        a->rightg->parentg = a;
    }
    if(b->parentg != nil) {
        if(b->parentg->leftg == a || b->parentg->leftg == b) {
            b->parentg->leftg = b;
        }
        else {
            b->parentg->rightg = b;
        }
    }
    if(b->leftg != nil) {
        b->leftg->parentg = b;
    }
    if(b->rightg != nil) {
        b->rightg->parentg = b;
    }
}*/
void swap_child_pointers(thirdnode* a, thirdnode* a_parent, thirdnode* b, thirdnode* b_parent) {
    if (a_parent != NULL) {
        if (a_parent->leftg == a) {
            a_parent->leftg = b;
        } else {
            a_parent->rightg = b;
        }
    }
    if (b_parent != NULL) {
        if (b_parent->leftg == b) {
            b_parent->leftg = a;
        } else {
            b_parent->rightg = a;
        }
    }
}
void swap_parent_pointers(thirdnode* a, thirdnode* a_parent, thirdnode* b, thirdnode* b_parent) {
    if (a != NULL) {
        a->parentg = b_parent;
    }
    if (b != NULL) {
        b->parentg = a_parent;
    }
}

void swap(thirdnode *a, thirdnode *b) {
    if (a == 0 || b == 0) {
        return;
    }
    swap_child_pointers(a, a->parentg, b, b->parentg);
    swap_parent_pointers(a, a->parentg, b, b->parentg);
    swap_parent_pointers(a->leftg, a, b->leftg, b);
    swap_child_pointers(a->leftg, a, b->leftg, b);
    swap_parent_pointers(a->rightg, a, b->rightg, b);
    swap_child_pointers(a->rightg, a, b->rightg, b);
    int old_a_color = a->color;
    a->color = b->color;
    b->color = old_a_color;
}


void group_structure::group_apply(command *c, int sock, name_structure* base_name, phone_structure* base_phone) {
     thirdnode *nd;
     thirdnode* check;
     switch(c->type) {
            case CMD_NONE: {
                printf("incorrect command\n");
                return;
            }
            case QUIT: {
                return;
            }
            case INSERT: {
                nd = new thirdnode(c->name, c->phone, c->group);
                this->add_node(nd);
                base_phone->hash[hash_fun_p(nd->phone)].add_head((secnode*)nd);
                base_name->hash[hash_fun_n(nd->name)].add_head((record_node*)nd);
                break;
            }
            case SELECT: {
                if(head == 0 || head == nil){return;}
                this->curr = this->head;
                if(c->c_group != EQ){
                    //nd = find_node(c->group, c->c_group);
                    //if(!nd) {
                    //    return;
                    //}
                    //if(c->c_group == LE || c->c_group == LT || c->c_group == GE || c->c_group == GT) {
                    //    this->apply_to_subtree(nd, c, fp, base_name, base_phone);
                    //    return;
                    //}
                    printf("ERR: group_structure with incorrect group operation.\n");
                    return;
                }
                nd = find_node(c->group);
                if(!nd){
                    return;
                }
                /*if(nd->apply(c) == 1) {
                    nd->fprint(fp);
                    fprintf(fp, " \n");
                }*/
                this->apply_to_listnode(nd, c, sock, base_name, base_phone);
                break;
            }
            case DELETE: {
                if(head == 0){return;}
                this->curr = this->head;
                if(c->c_group != EQ) {
                    //nd = find_node(c->group, c->c_group);
                    //if(!nd) {
                    //    return;
                    //}
                    //if(c->c_group == LE || c->c_group == LT || c->c_group == GE || c->c_group == GT) {
                        //==============
                    //    this->apply_to_subtree(nd, c, fp, base_name, base_phone);
                        //==============
                    //    return;
                    //}
                    printf("ERR: group_structure with incorrect group operation.\n");
                    return;
                }
                nd = find_node(c->group);
                if(!nd) {
                    return;
                }
                this->apply_to_listnode(nd, c, sock, base_name, base_phone);
                printf("check base_group for correct after apply_to_listnode...\n");
                check = this->check_for_null();
                if(check == 0) {
                    printf("It is correct for now.\n");
                }
                else {
                    printf("It is not correct for now!\n");
                    this->fprint();
                    printf("Doing while(True) for now.\n");
                    while(4);
                }
                if(nd->apply(c) == 1) {
                    this->del_node(nd);
                    base_name->force_del((record_node*)(nd));
                    base_phone->force_del((secnode*)(nd));
                    delete nd;
                }
                break;
            }
        }
}

void group_structure::apply_to_listnode(thirdnode* nd, command* c, int sock, name_structure* base_name, phone_structure* base_phone) {
    thirdnode* delnode;
    //thirdnode* start_node;//list_head;
    switch(c->type) {
        case CMD_NONE: {
            printf("incorrect list_command\n");
            return;
        }
        case QUIT: {return;}
        case INSERT: {printf("Warning: Do not insert in \"apply_to_listnode\".\n");return;}
        case SELECT: {
            while(nd && nd != nil) {
                if(nd->apply(c) == 1) {
                    nd->sprint(sock);
                    //fprintf(fp, " \n");
                }
                if(nd == nd->equalg) {// BREAK IT DOWN NOW!!!!!
                    //nd->equalg = 0;
                    break;
                }
                nd = nd->equalg;
            }
            break;
        }
        case DELETE: {
            //start_node = nd;
            while(nd->equalg && nd->equalg != nil) {
                if(nd->equalg->apply(c) == 1) {
                    //delnode = nd->equalg;
                    //nd->equalg = nd->equalg->equalg;
                    delnode = del_nextg(nd);
                    base_name->force_del((record_node*)(delnode));
                    base_phone->force_del((secnode*)(delnode));
                    delete delnode;
                }
                else {
                    //if(nd == nd->equalg) {// BREAK IT DOWN NOW!!!!!
                        //nd->equalg = 0;
                    //    break;
                    //}
                    nd = nd->equalg;
                }
            }

            /*if(start_node->equalg && start_node->apply(c) == 1) {
                delnode = start_node;
                start_node = start_node->equalg;
                if(this->start_node == delnode) {
                    this->start_node = delnode->equalg;
                }
                if(this->curr == delnode) {
                    curr = delnode->equalg;
                }

                start_node->parentg = delnode->parentg;
                start_node->leftg = delnode->leftg;
                start_node->rightg = delnode->rightg;

                if(delnode->parentg != nil) {
                    if(delnode->parentg->leftg == delnode) {
                        delnode->parentg->leftg = start_node;
                    }
                    else {
                        delnode->parentg->rightg = start_node;
                    }
                }
                if(delnode->leftg != nil) {
                    delnode->leftg->parentg = start_node;
                }
                if(delnode->rightg != nil) {
                    delnode->rightg->parentg = start_node;
                }
            }*/
        }
    }
}

thirdnode* del_nextg(thirdnode* nd) {
    thirdnode *del_nd;
    if(nd->equalg) {
        del_nd = nd->equalg;
        nd->equalg = del_nd->equalg;
        return del_nd;
    }
    return 0;
}
void group_structure::force_base(name_structure *base) {
    /*if (this->nil->parentg && this->nil->parentg->group != 0) {
        printf("FAILED: NIL parent GROUP: %d", this->nil->parentg->group);
        return;
    }*/

    int i = 0;
    for(i = 0; i < NAME_HASH_LEN; i++) {
        base->hash[i].curr = base->hash[i].head;
    }
    i = 0;
    while(i < NAME_HASH_LEN) {
        if(base->hash[i].curr) {
            //hash[hash_fun_p(base->hash[i].curr->phone)].add_head((secnode*)(base->hash[i].curr));
            this->add_node((thirdnode*)(base->hash[i].curr));
            /*if (this->nil->parentg && this->nil->parentg->group != 0) {
                printf("FAILED IN CYCLE: NIL parent GROUP: %d", this->nil->parentg->group);
                return;
            }*/
            base->hash[i].curr = base->hash[i].curr->nextn;
        }
        else {
            i++;
        }
    }
}




void group_structure::force_del(thirdnode* nd, thirdnode* start, int first)
{
    int res;
    thirdnode* runner;
    thirdnode* mem;

    if(first) {
        first = 0;
        start = head;
    }
    if(start == nil) return; 
    res = cmp(start->group, nd->group);
    if(res == 0) {
        for(runner = start->equalg, mem = start; runner; mem = runner, runner = runner->equalg) {
            if(runner == nd) {
                del_nextg(mem);
                return;
            }
        }
        if(start == nd) {
            del_node(start);
            return;
        }
    }
    if(res > 0) force_del(nd, start->leftg, first);
    if(res < 0) force_del(nd, start->rightg, first);
}



/*void group_structure::force_del(thirdnode* nd) {
    thirdnode* another;
    if(nd == 0 || nd == nil){
        return;
    }
    another = find_node(nd->group);
    if(another == nd) {
        this->del_node(nd);
        return;
    }
    if(another)
    for(;another->equalg; another = another->equalg) {
        if(another->equalg == nd) {
            del_nextg(another);
            return;
        }
    }
    this->del_node(nd);
    return;
    
/////////////////////////

    if(nd == 0 || nd == nil){
        return;
    }
    if(head == nil) {
        return;
    }
    //printf("HERE312\n");
    //head->fprint();
    //this->fprint();
    //printf("HERE314\n");
    another = this->find_node(nd->group);
    //printf("HERE313\n");
    if(another == 0 || another == nil) {
        return;
    }
    if(another != nd) {
        while(another && another != nil) {
            if(another->equalg == nd){
                del_nextg(another);
                return;
           }
           if(another == another->equalg) {
                // BREAK IT DOWN NOW!!!!!
                break;
           }
            another = another->equalg;
        }
        return;
    }
    //printf("HERE_20o\n");
    if(another->equalg && another->equalg != nil){
        if(another == head) {
            head = another->equalg;
        }
        if(another->parentg && another->parentg != nil) { // BREAK IT
            if(another->parentg->leftg == another) {
                another->parentg->leftg = another->equalg;
            }
            else {
                another->parentg->rightg = another->equalg;
            }
        }
        if(another->leftg && another->leftg != nil) {// BREAK IT
            another->leftg->parentg = another->equalg;
        }
        if(another->rightg && another->rightg != nil) {// BREAK IT
            another->rightg->parentg = another->equalg;
        }
        another->equalg->parentg = another->parentg;
        another->equalg->leftg = another->leftg;
        another->equalg->rightg = another->rightg;
        another->equalg->color = another->color;
        return;
    }
}*/



















































/*int main(void)
{
	int group;
    int secgroup;
	char fake_name[400] = "fake_name\0";
	group_structure base;
	thirdnode *new_thirdnode;
    while (4) {
    	printf("new group = ");
    	scanf("%d", &group);
    	//printf("\n");
    	if(group > 0) {
    		new_thirdnode = new thirdnode(fake_name, 0, group);
    		//printf("1\n");
    		base.add_node(new_thirdnode);
    		//printf("2\n");
    		continue;
    	}
    	else {
    		if(group == 0) {
    			printf("delete group = ");
    			scanf("%d", &group);
    			printf("\n");
    			if(group == 0) {
    				base.print();
    				continue;
    			}
                if(group == -1) {
                    base.print();
                    printf("swap1 = ");
                    scanf("%d", &group);
                    //printf("\n");
                    printf("swap2 = ");
                    scanf("%d", &secgroup);
                    //printf("\n");
                    swap(base.find_node(group), base.find_node(secgroup));
                    base.print();
                    continue;
                }
    			if(base.find_node(group) == 0) {
    				printf("ERR: Cannot find delete_node\n");
    				return -1;
    			}
    			new_thirdnode = base.del_node(base.find_node(group));
    			printf("D\n");
    			del(new_thirdnode);
    			//delete new_thirdnode;
                continue;
    		}
    		break;
    	}
    }
	return 0;
}*/

/*void del(thirdnode* new_thirdnode) {
	if(new_thirdnode->equalg) {
	del(new_thirdnode->equalg);
	delete new_thirdnode;
	return;
	}
}*/
