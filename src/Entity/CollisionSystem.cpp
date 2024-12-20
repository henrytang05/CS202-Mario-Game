// #include "Entity/CollisionSystem.h"
// #include "AbstractEntity.h"
// #include "Components/EnemyComponents.h"
// #include "pch.h"
// #include "raylib.h"
// bool isCollision(Rectangle a, Rectangle b) {
//   return (a.x <= b.x + b.width && a.x + a.width >= b.x &&
//           a.y <= b.y + b.height && a.y + a.height >= b.y);
// // }
// Shared<AbstractEntity>
// CollisionSystem::standingOn(Rectangle box, Shared<AbstractEntity> entity) {
//   for (auto &e : entities)
//     if (*e != *entity) {
//       EnemyPosition &otherPosition = e->getComponent<EnemyPosition>();
//       EnemySize &otherSize = e->getComponent<EnemySize>();
//       Rectangle otherBox = {otherPosition.x, otherPosition.y, otherSize.x,
//                             otherSize.y};
//
//       if (isCollision(thisBoundingBox.getBotLeft(),
//                       otherBoundingBox.getBotRight()) &&
//           isCollision(thisBoundingBox.getTopLeft(),
//                       otherBoundingBox.getTopRight()))
//         continue;
//       if (isCollision(thisBoundingBox.getBotRight(),
//                       otherBoundingBox.getBotLeft()) &&
//           isCollision(thisBoundingBox.getTopRight(),
//                       otherBoundingBox.getTopLeft()))
//         continue;
//       if (isCollision(thisBoundingBox.getBotLeft(),
//                       otherBoundingBox.getTopLeft()))
//         return e;
//       if (isCollision(thisBoundingBox.getBotLeft(),
//                       otherBoundingBox.getTopRight()))
//         return e;
//       if (isCollision(thisBoundingBox.getBotRight(),
//                       otherBoundingBox.getTopLeft()))
//         return e;
//       if (isCollision(thisBoundingBox.getBotRight(),
//                       otherBoundingBox.getTopRight()))
//         return e;
//     }
//   return nullptr;
// }
