#include "Core/Primitives/MyCircle.hpp"

using namespace DX3D;

extern float WINDOW_WIDTH_LIMITS;
extern float WINDOW_HEIGHT_LIMITS;
extern float MAXIMUM_BALL_SPEED;
extern float MINIMUM_BALL_SPEED;
extern bool LOG_BALL_BOUNCES;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyCircle::MyCircle() : triangles{
MyTriangle(
    MyVertex(
        0.0000f, 0.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Bottom-left
    MyVertex(
        1.0000f, 0.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Top-right
    MyVertex(
        0.9239f, -0.3827f, 0.0f,
        1.0f, 1.0f, 1.0f
    ) // Bottom-right
),
MyTriangle(
    MyVertex(
        0.0000f, 0.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Bottom-left
    MyVertex(
        0.9239f, -0.3827f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Top-right
    MyVertex(
        0.7071f, -0.7071f, 0.0f,
        1.0f, 1.0f, 1.0f
    ) // Bottom-right
),
MyTriangle(
    MyVertex(
        0.0000f, 0.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Bottom-left
    MyVertex(
        0.7071f, -0.7071f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Top-right
    MyVertex(
        0.3827f, -0.9239f, 0.0f,
        1.0f, 1.0f, 1.0f
    ) // Bottom-right
),
MyTriangle(
    MyVertex(
        0.0000f, 0.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Bottom-left
    MyVertex(
        0.3827f, -0.9239f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Top-right
    MyVertex(
        0.0000f, -1.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ) // Bottom-right
),
MyTriangle(
    MyVertex(
        0.0000f, 0.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Bottom-left
    MyVertex(
        0.0000f, -1.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Top-right
    MyVertex(
        -0.3827f, -0.9239f, 0.0f,
        1.0f, 1.0f, 1.0f
    ) // Bottom-right
),
MyTriangle(
    MyVertex(
        0.0000f, 0.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Bottom-left
    MyVertex(
        -0.3827f, -0.9239f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Top-right
    MyVertex(
        -0.7071f, -0.7071f, 0.0f,
        1.0f, 1.0f, 1.0f
    ) // Bottom-right
),
MyTriangle(
    MyVertex(
        0.0000f, 0.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Bottom-left
    MyVertex(
        -0.7071f, -0.7071f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Top-right
    MyVertex(
        -0.9239f, -0.3827f, 0.0f,
        1.0f, 1.0f, 1.0f
    ) // Bottom-right
),
MyTriangle(
    MyVertex(
        0.0000f, 0.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Bottom-left
    MyVertex(
        -0.9239f, -0.3827f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Top-right
    MyVertex(
        -1.0000f, 0.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ) // Bottom-right
),
MyTriangle(
    MyVertex(
        0.0000f, 0.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Bottom-left
    MyVertex(
        -1.0000f, 0.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Top-right
    MyVertex(
        -0.9239f, 0.3827f, 0.0f,
        1.0f, 1.0f, 1.0f
    ) // Bottom-right
),
MyTriangle(
    MyVertex(
        0.0000f, 0.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Bottom-left
    MyVertex(
        -0.9239f, 0.3827f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Top-right
    MyVertex(
        -0.7071f, 0.7071f, 0.0f,
        1.0f, 1.0f, 1.0f
    ) // Bottom-right
),
MyTriangle(
    MyVertex(
        0.0000f, 0.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Bottom-left
    MyVertex(
        -0.7071f, 0.7071f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Top-right
    MyVertex(
        -0.3827f, 0.9239f, 0.0f,
        1.0f, 1.0f, 1.0f
    ) // Bottom-right
),
MyTriangle(
    MyVertex(
        0.0000f, 0.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Bottom-left
    MyVertex(
        -0.3827f, 0.9239f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Top-right
    MyVertex(
        0.0000f, 1.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ) // Bottom-right
),
MyTriangle(
    MyVertex(
        0.0000f, 0.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Bottom-left
    MyVertex(
        0.0000f, 1.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Top-right
    MyVertex(
        0.3827f, 0.9239f, 0.0f,
        1.0f, 1.0f, 1.0f
    ) // Bottom-right
),
MyTriangle(
    MyVertex(
        0.0000f, 0.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Bottom-left
    MyVertex(
        0.3827f, 0.9239f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Top-right
    MyVertex(
        0.7071f, 0.7071f, 0.0f,
        1.0f, 1.0f, 1.0f
    ) // Bottom-right
),
MyTriangle(
    MyVertex(
        0.0000f, 0.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Bottom-left
    MyVertex(
        0.7071f, 0.7071f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Top-right
    MyVertex(
        0.9239f, 0.3827f, 0.0f,
        1.0f, 1.0f, 1.0f
    ) // Bottom-right
),
MyTriangle(
    MyVertex(
        0.0000f, 0.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Bottom-left
    MyVertex(
        0.9239f, 0.3827f, 0.0f,
        1.0f, 1.0f, 1.0f
    ), // Top-right
    MyVertex(
        1.0000f, 0.0000f, 0.0f,
        1.0f, 1.0f, 1.0f
    ) // Bottom-right
)
}, bounceDirection(MyVec3(0.0f)), centerDelta(MyVec3(0.0f)) {
    std::random_device randomDevice;
    std::mt19937 numberGenerator(randomDevice());
    std::uniform_real_distribution<float> randomSpeed(MINIMUM_BALL_SPEED, MAXIMUM_BALL_SPEED);
    this->xSpeed = randomSpeed(numberGenerator);
    this->ySpeed = randomSpeed(numberGenerator);
    this->bounceDirection.x = (this->xSpeed > 0) ? 1.0f : -1.0f;
    this->bounceDirection.y = (this->ySpeed > 0) ? 1.0f : -1.0f;
}
MyCircle::~MyCircle() {}
void MyCircle::Update(float deltaTime) {
    std::vector<MyVertex> vertices = this->GetVertices();
    this->top = vertices[35];
    this->bottom = vertices[11];
    this->left = vertices[23];
    this->right = vertices[1];

    //* Hit Right Wall
    if (this->right.position.x >= WINDOW_WIDTH_LIMITS) {
        if (LOG_BALL_BOUNCES)std::cout << "Ball hit Right Wall" << std::endl;
        this->bounceDirection.x = -1;
    }
    //* Hit Left Wall
    if (this->left.position.x <= -WINDOW_WIDTH_LIMITS) {
        if (LOG_BALL_BOUNCES)std::cout << "Ball hit Left Wall" << std::endl;
        this->bounceDirection.x = 1;
    }
    //* Hit Ceiling
    if (this->top.position.y >= WINDOW_HEIGHT_LIMITS) {
        if (LOG_BALL_BOUNCES)std::cout << "Ball hit Ceiling" << std::endl;
        this->bounceDirection.y = -1;
    }
    //* Hit Floor
    if (this->bottom.position.y <= -WINDOW_HEIGHT_LIMITS) {
        if (LOG_BALL_BOUNCES)std::cout << "Ball hit Floor" << std::endl;
        this->bounceDirection.y = 1;
    }

    this->centerDelta += MyVec3((this->xSpeed * this->bounceDirection.x) * deltaTime,
        (this->ySpeed * this->bounceDirection.y) * deltaTime,
        0.0f);
    // std::cout << "centerDelta: (" << centerDelta.x << ", " << centerDelta.y << ", " << centerDelta.z << ")" << std::endl;
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
