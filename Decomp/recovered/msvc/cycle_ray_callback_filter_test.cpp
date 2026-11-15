struct BroadphaseProxy {
    unsigned char reserved[4];
    unsigned short collisionGroup;
    unsigned short collisionMask;
};

class RayCallback {
    unsigned char reserved[12];
    unsigned short collisionGroup;
    unsigned short collisionMask;
public:
    bool needsCollision(const BroadphaseProxy* proxy) const;
};

bool RayCallback::needsCollision(const BroadphaseProxy* proxy) const {
    return (proxy->collisionGroup & collisionMask) != 0 &&
           (proxy->collisionMask & collisionGroup) != 0;
}
