//
// Singleton.h for babel in /home/valens_a//projets/rendu/babel/repo/src/client
//
// Made by arnaud valensi
// Login   <valens_a@epitech.net>
//
// Started on  Tue May 15 11:21:38 2012 arnaud valensi
// Last update Sun May 27 17:18:52 2012 johan rogel
//

#ifndef SINGLETON_H_
#define SINGLETON_H_

/*!
 * \class Singleton
 * \brief Singleton templated class.
 */

template <class T>
class Singleton
{
public:
  static T*	getInstance();
  ~Singleton();

private:
  static T	*instance;

  Singleton();
  Singleton(Singleton const &other);
  Singleton&	operator=(Singleton const &other);
};

template <class T>
T		*Singleton<T>::instance = 0;

/*!
 * \fn T *Singleton<T>::getInstance()
 * \return Instance of the class.
 * \brief Get class instance.
 */

template <class T>
T		*Singleton<T>::getInstance()
{
  if (!instance)
    instance = new T();
  return (instance);
}

/*!
 * \fn Singleton<T>::Singleton()
 * \brief constructor.
 */

template <class T>
Singleton<T>::Singleton()
{

}

/*!
 * \fn Singleton<T>::~Singleton()
 * \brief Destructor.
 */

template <class T>
Singleton<T>::~Singleton()
{

}

/*!
 * \fn Singleton<T>&		Singleton<T>::operator=(Singleton const &other)
 * \param Reference on a Singleton instance.
 * \return Reference on the current Singleton instance.
 * \brief Only to hide the default assignment operator.
 */

template <class T>
Singleton<T>&		Singleton<T>::operator=(Singleton const &other)
{
  (void) other;
  return (*this);
}

#endif
