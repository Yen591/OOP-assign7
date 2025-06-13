#ifndef ELEMENT_H
#define ELEMENT_H

#include "icon.h"
#include "unit.h"
#include "collider.h"
#include <iostream>
#include <vector>
class GameObject : public ICollider {

	public:
		GameObject(Icon icon, Position pos = {0, 0});

		virtual ~GameObject();
		virtual void update();
		Icon getIcon() const;
		void setDirection(Direction);
		Vec2 getPosition() const;
		bool isAlive() const;

		virtual bool intersect(ICollider* other) override;
		virtual void onCollision(ICollider* other) override;

	protected:
		Direction _dir;
		Vec2 _pos;
		Icon _icon;
		bool _alive = true;
};

inline Icon GameObject::getIcon() const { return _icon; }

inline Vec2 GameObject::getPosition() const { return _pos; }
#endif
