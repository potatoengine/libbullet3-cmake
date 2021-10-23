Modern CMake build script for the primary library portion of Bullet3.

CMake script by Sean Middleditch. All Bullet3 source code is by
the upstream Bullet authors, and is unmodified by this repository.

Upstream sources at https://github.com/bulletphysics/bullet3

Supported Bullet3 sub-libraries:

 - Bullet3Collision
 - Bullet3Common
 - Bullet3Dynamics
 - Bullet3Geometry
 - BulletDynamics
 - BulletCollision
 - BulletInverseDynamics
 - BulletSoftBody
 - LinearMath

 Differences:

 - Single library named libbullet3
 - May be built as a DLL on Windows

 Supported CMake options:

- `LIBBULLET3_BUILD_SHARED` :: Build as a shared library. Defaults to the value of `BUILD_SHARED_LIBS`.
- `LIBBULLET3_BUILD_TESTS` :: Builds a simple test program. Defaults to `OFF` if built as a subdirectory, or `ON` otherwise.

Unsupported Bullet3 modules:

 - No upstream tests
 - No examples or harness
 - No OpenCL
 - No extras