// Copyright 2021 SMS
// License(Apache-2.0)

// Core
#include "Clem/Core/Core.h"

// Scene
#include "Clem/Scene/Entity.h"
#include "Clem/Scene/Scene.h"

// Renderer
#include "Clem/Renderer/Camera.h"
#include "Clem/Renderer/Framebuffer.h"
#include "Clem/Renderer/Output.h"
#include "Clem/Renderer/Sprite.h"

// Physics
#include "Clem/Physics/BoxCollider.h"
#include "Clem/Physics/CircleCollider.h"
#include "Clem/Physics/Collider.h"
#include "Clem/Physics/Rigidbody.h"

// Component
#include "Clem/Component/Component.h"
#include "Clem/Component/Script.h"
#include "Clem/Component/Tag.h"
#include "Clem/Component/Transform.h"

// Event
#include "Clem/Events/Event.h"
#include "Clem/Events/EventDispatcher.h"
#include "Clem/Events/KeyEvent.h"
#include "Clem/Events/MouseEvent.h"

// Audio
#include "Clem/Audio/Audio.h"
#include "Clem/Audio/Source.h"

#include "Clem/Assert.h"

#include "Clem/Log.h"
#include "Clem/Platform.h"
#include "Clem/Profiler.h"
#include "Clem/Random.h"
#include "Clem/Window.h"
