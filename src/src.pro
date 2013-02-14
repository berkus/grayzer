TEMPLATE       = lib
TARGET         = grayzer

CONFIG         -= qt
INCLUDEPATH    = ../include

SOURCES        = Camera.cpp \
                 ColorTable.cpp \
		 Draw.cpp \
		 Stats.cpp \
		 Noise.cpp \
		 Shade.cpp \
		 Tracer.cpp \
		 environment/Environment.cpp \
		 environment/Fog.cpp \
		 go/GeomObj.cpp \
		 go/Box.cpp \
		 go/Cylinder.cpp \
		 go/Plane.cpp \
		 go/Rect.cpp \
		 go/Sphere.cpp \
		 go/Triangle.cpp \
		 image/Targa.cpp \
		 light/PointLight.cpp \
		 light/SphericLight.cpp \
		 light/SpotLight.cpp \
		 math/Matrix.cpp \
		 math/Projection.cpp \
		 render/Render.cpp \
		 render/DRender.cpp \
		 render/ADRender.cpp \
		 texture/Bozo.cpp \
		 texture/Brick.cpp \
		 texture/BumpMap.cpp \
		 texture/Bumps.cpp \
		 texture/Checker.cpp \
		 texture/ColorMap.cpp \
		 texture/Dents.cpp \
		 texture/Gloss.cpp \
		 texture/Gradient.cpp \
		 texture/Granite.cpp \
		 texture/Marble.cpp \
		 texture/Ripples.cpp \
		 texture/Wood.cpp \
		 texture/Wrinkles.cpp
