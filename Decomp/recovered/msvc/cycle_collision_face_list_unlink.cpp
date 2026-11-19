struct CollisionFace {
    unsigned reserved[12];
    CollisionFace* previous;
    CollisionFace* next;
};
struct CollisionFaceList {
    CollisionFace* head;
    unsigned count;
};
void __fastcall candidate_fragment(CollisionFaceList* list, CollisionFace* face) {
    if (face->next) face->next->previous = face->previous;
    if (face->previous) face->previous->next = face->next;
    if (face == list->head) list->head = face->next;
    --list->count;
}
