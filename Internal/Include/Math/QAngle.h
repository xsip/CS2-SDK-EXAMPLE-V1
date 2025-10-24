#pragma once
// used: [crt] isfinite, fmodf, remainderf
#include <cmath>
#include <Math/Definitions.h>
#include <Math/Vector.h>
#include <Math/Core.h>
// #include "Math.hpp"
// used: clamp
// #include "../../utilities/crt.h"

// forward declarations
struct Matrix3x4_t;

struct QAngle_t
{
	QAngle_t(float x = 0.f, float y = 0.f, float z = 0.f);

	QAngle_t(const float* arrAngles);

#pragma region qangle_array_operators

	[[nodiscard]] float& operator[](const int nIndex);

	[[nodiscard]] const float& operator[](const int nIndex) const;

#pragma endregion

#pragma region qangle_relational_operators

	bool operator==(const QAngle_t& angBase) const;

	bool operator!=(const QAngle_t& angBase) const;

#pragma endregion

#pragma region qangle_assignment_operators

	 QAngle_t& operator=(const QAngle_t& angBase);

#pragma endregion

#pragma region qangle_arithmetic_assignment_operators

	 QAngle_t& operator+=(const QAngle_t& angBase);

	 QAngle_t& operator-=(const QAngle_t& angBase);

	 QAngle_t& operator*=(const QAngle_t& angBase);
	 QAngle_t& operator/=(const QAngle_t& angBase);

	 QAngle_t& operator+=(const float flAdd);

	 QAngle_t& operator-=(const float flSubtract);

	 QAngle_t& operator*=(const float flMultiply);
	 QAngle_t& operator/=(const float flDivide);

#pragma endregion

#pragma region qangle_arithmetic_unary_operators

	 QAngle_t& operator-();

	 QAngle_t operator-() const;

#pragma endregion

#pragma region qangle_arithmetic_ternary_operators

	 QAngle_t operator+(const QAngle_t& angAdd) const;

	 QAngle_t operator-(const QAngle_t& angSubtract) const;

	 QAngle_t operator*(const QAngle_t& angMultiply) const;

	 QAngle_t operator/(const QAngle_t& angDivide) const;
	 QAngle_t operator+(const float flAdd) const;

	 QAngle_t operator-(const float flSubtract) const;

	 QAngle_t operator*(const float flMultiply) const;

	 QAngle_t operator/(const float flDivide) const;
#pragma endregion

	// @returns : true if each component of angle is finite, false otherwise
	[[nodiscard]] bool IsValid() const;
	/// @returns: true if each component of angle equals to another, false otherwise
	[[nodiscard]] bool IsEqual(const QAngle_t& angEqual, const float flErrorMargin = std::numeric_limits<float>::epsilon()) const;
	/// @returns: true if each component of angle equals zero, false otherwise
	[[nodiscard]] bool IsZero() const;

	/// @returns: length of hypotenuse
	[[nodiscard]] float Length2D() const;

	/// clamp each angle component by minimal/maximal allowed value for source sdk games
	/// @returns: clamped angle
	 QAngle_t& ClampAngle();
	/// map polar angles to the range of [-180, 180] degrees
	/// @returns: normalized angle
	QAngle_t& Normalize();
	/// convert angle to direction vectors
	/// @param[out] pvecForward [optional] output for converted forward vector
	/// @param[out] pvecRight [optional] output for converted right vector
	/// @param[out] pvecUp [optional] output for converted up vector
	void ToDirections(Vector* pvecForward, Vector* pvecRight = nullptr, Vector* pvecUp = nullptr) const;
	float DistanceTo(const QAngle_t& other) const;

	Vector AngleToDirection();
	/// @param[in] vecOrigin [optional] origin for converted matrix
	/// @returns: matrix converted from angle
	[[nodiscard]] Matrix3x4_t ToMatrix(const Vector& vecOrigin = {}) const;

public:
	float x = 0.0f, y = 0.0f, z = 0.0f;
};

using QAngle = QAngle_t;