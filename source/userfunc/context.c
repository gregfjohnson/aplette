#include <string.h>
#include "apl.h"
#include "memory.h"
#include "userfunc.h"

Context *Context_new() {
    Context *context = (Context *) alloc(sizeof(Context));
    memset(context, 0, sizeof(Context));
}

void Context_addShadowedId(Context *context, SymTabEntry *entry) {
    // "realloc" shadowedId vector if necessary..
    //
    if (context->shadowedIdCount == context->shadowedIdSize) {
        context->shadowedIdSize = 1 + 2 * context->shadowedIdSize;

        int size = context->shadowedIdSize * sizeof(SymTabEntry*);
        SymTabEntry **entries = (SymTabEntry **) alloc(size);

        memcpy(entries,
               context->shadowedIds,
               context->shadowedIdCount * sizeof(SymTabEntry*));

        aplfree((int *) context->shadowedIds);

        context->shadowedIds = entries;
    }

    context->shadowedIds[context->shadowedIdCount++] = entry;
}
