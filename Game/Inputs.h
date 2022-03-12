#pragma once


struct Inputs
{
  /// <summary>
    /// Indique si le joueur doit faire feu lors de la prochaine mise � jour
    /// </summary>
  bool shouldFire;

  /// <summary>
  /// Pouss�e � appliquer au personnage en X
  /// </summary>
  float speedValueX;

  /// <summary>
  /// Pouss�e � appliquer au personnage en Y
  /// </summary>
  float speedValueY;

  /// <summary>
  /// Rotation � appliquer au personnage
  /// </summary>
  float rotationValue;

  inline void reset()
  {
    shouldFire = false;
    speedValueX=speedValueY=rotationValue=0;
  }
};