#include <stdbool.h>
#include <string.h>
#include "apl.h"
#include "rbtree.h"
#include "memory.h"
#include "utility.h"

static rbtree_t rbSymbolTable;

static int symTabCmp(SymTabEntry* e1, SymTabEntry* e2) {
    if (e1->namep == NULL && e2->namep == NULL) return 0;
    if (e1->namep == NULL && e2->namep != NULL) return -1;
    if (e1->namep != NULL && e2->namep == NULL) return  1;
    return strcmp(e1->namep, e2->namep);
}

void symtab_init() {
    rbtree_init(&rbSymbolTable, (rbtree_cmp_t*)&symTabCmp);
    rbtree_set_malloc_free(&rbSymbolTable,
                           (rbtree_malloc_t*) &alloc,
                           (rbtree_free_t*) &aplfree);
}

void symtab_clear() {
    SymTabEntry *entry;
    while ((entry = rbtree_first(&rbSymbolTable)) != NULL) {
        rbtree_delete(&rbSymbolTable, entry);
        aplfree(entry);
    }
}

SymTabEntry* symtabFind(char* name) {
    SymTabEntry entry;
    if (name == NULL) { return NULL; }
    entry.namep = name;
    return rbtree_find(&rbSymbolTable, &entry);
}

void symtabEntryInsert(SymTabEntry* entry) {
    rbtree_insert(&rbSymbolTable, entry);
}

SymTabEntry* symtabEntryCreate(char* name) {
    SymTabEntry* entry;
    if (name == NULL) { return NULL; }

    entry = (SymTabEntry*)alloc(sizeof(SymTabEntry));

    if (entry == NULL) { error(ERR_botch, "out of memory"); }

    memset(entry, 0, sizeof(SymTabEntry));
    entry->namep = strdup(name);

    return entry;
}

SymTabEntry* symtabInsert(char* name) {
    SymTabEntry* entry = symtabEntryCreate(name);
    if (entry != NULL) {
        rbtree_insert(&rbSymbolTable, entry);
    }
    return entry;
}

void symtabDelete(char* name) {
    SymTabEntry entry, *found;
    entry.namep = name;
    found = rbtree_delete(&rbSymbolTable, &entry);
    if (found) {
        aplfree(found);
    }
}

void symtabRemoveEntry(SymTabEntry* entry) {
    rbtree_delete(&rbSymbolTable, entry);
}

static rbtree_iter_t symTabIter;
static bool symTabIterInUser = false;

void symtabIterateInit()
{
    if (symTabIterInUser) {
        error(ERR_botch, "multiple users of symbol table iterator");
    }
    symTabIterInUser = true;
    symTabIter = rbtree_iter(&rbSymbolTable);
}

SymTabEntry* symtabIterate()
{
    SymTabEntry* result;
    if (!symTabIterInUser) {
        error(ERR_botch, "symbol table iterator not initialized");
    }
    result = rbtree_iter_next(&symTabIter);
    if (result == NULL) {
        symTabIterInUser = false;
    }

    return result;
}
