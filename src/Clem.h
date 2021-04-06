﻿// Copyright 2021 SMS
// License(Apache-2.0)

#include "Clem/Core/Core.h"
#include "Clem/Rendering/Rendering.h"
#include "Clem/Components/Components.h"

// Scene
#include "Clem/Scene/Entity.h"
#include "Clem/Scene/Scene.h"

// Physics
#include "Clem/Physics/BoxCollider.h"
#include "Clem/Physics/CircleCollider.h"
#include "Clem/Physics/Collider.h"
#include "Clem/Physics/Rigidbody.h"

// Events
#include "Clem/Events/Event.h"
#include "Clem/Events/EventDispatcher.h"
#include "Clem/Events/KeyEvent.h"
#include "Clem/Events/MouseEvent.h"

// Audio
#include "Clem/Audio/Audio.h"
#include "Clem/Audio/Source.h"
#include "Clem/Audio/Sound.h"

#include "Clem/Assert.h"
#include "Clem/Log.h"
#include "Clem/Platform.h"
#include "Clem/Profiler.h"
#include "Clem/Random.h"
#include "Clem/Window.h"
