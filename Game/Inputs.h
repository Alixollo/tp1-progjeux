#pragma once


struct Inputs
{
  /// <summary>
    /// Indique si le joueur doit faire feu lors de la prochaine mise à jour
    /// </summary>
  bool shouldFire;

  /// <summary>
  /// Poussée à appliquer au personnage en X
  /// </summary>
  float speedValueX;

  /// <summary>
  /// Poussée à appliquer au personnage en Y
  /// </summary>
  float speedValueY;

  /// <summary>
  /// Rotation à appliquer au personnage
  /// </summary>
  float rotationValue;

  inline void reset()
  {
    shouldFire = false;
    speedValueX=speedValueY=rotationValue=0;
  }
};