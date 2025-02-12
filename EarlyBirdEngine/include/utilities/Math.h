#pragma once 

#include "SFML/Graphics.hpp"

namespace eb
{
    // Vectors

    /* DegreesToRadians: Converts an angle from degrees to radians.
       - Use case: When you need to work with trigonometric functions that require radians.
       - Example: float radians = DegreesToRadians(90.f); // Returns 1.5708 (PI/2) */
    float DegreesToRadians(const float degrees);

    /* RadiansToDegrees: Converts an angle from radians to degrees.
       - Use case: When you need to display or use angles in degrees.
       - Example: float degrees = RadiansToDegrees(1.5708f); // Returns 90 */
    float RadiansToDegrees(const float radians);

    /* RotationToVector: Converts a rotation angle (in degrees) to a unit vector.
       - Use case: When you need to convert a rotation into a direction vector (e.g., for movement).
       - Example: sf::Vector2f direction = RotationToVector(45.f); // Returns (0.707, 0.707) */
    sf::Vector2f RotationToVector(const float rotation);

    /* GetVectorLength: Calculates the length (magnitude) of a 2D vector.
       - Use case: When you need to determine the distance or magnitude of a vector.
       - Example: float length = GetVectorLength(sf::Vector2f(3.f, 4.f)); // Returns 5 */
    template<typename T>
    float GetVectorLength(const sf::Vector2<T> vector)
    {
        return std::sqrt(vector.x * vector.x + vector.y * vector.y);
    }

    /* NormalizeVector: Normalizes a 2D vector (converts it to a unit vector).
       - Use case: When you need a vector with the same direction but a length of 1.
       - Example: sf::Vector2f normalized = NormalizeVector(sf::Vector2f(3.f, 4.f)); // Returns (0.6, 0.8) */
    template<typename T>
    sf::Vector2<T>& NormalizeVector(sf::Vector2<T> vectorToNoramize)
    {
        // Calculate the length of the vector
        float vectorLength = GetVectorLength<T>(vectorToNoramize);

        // If the length is 0, return the original vector (cannot normalize a zero vector)
        if (vectorLength == 0.f)
            return vectorToNoramize;

        // Calculate the scale factor to normalize the vector
        float scaleFactor = 1 / vectorLength;

        // Scale the vector components to normalize it
        vectorToNoramize.x *= scaleFactor;
        vectorToNoramize.y *= scaleFactor;

        return vectorToNoramize;
    }

    // Random

    /* RandomRange: Generates a random float value within a specified range [min, max].
       - Use case: When you need random values for gameplay mechanics (e.g., random spawn positions, damage values).
       - Example: float randomValue = RandomRange(1.f, 10.f); // Returns a random value between 1 and 10 */
    float RandomRange(float min, float max);
}