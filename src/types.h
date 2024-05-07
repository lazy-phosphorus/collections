#ifndef __COLLECTIONS_TYPES__
#define __COLLECTIONS_TYPES__

typedef enum { FALSE = 0, TRUE = 1 } Bool;

/**
 * @brief Compare two values and determine which is larger.
 *
 * @return int If the former > the latter, returned value should > 0. If the
 * former == the latter, returned value should == 0. If the former < the latter,
 * returned value should < 0.
 */
typedef int CompareFunction(const void *, const void *);

/**
 * @brief Determine whether value satisfy some conditions or not.
 *
 * @return int If conditions are satisfied, `TRUE` should be returned.
 * Otherwise, `FALSE` should be returned.
 */
typedef Bool TestFunction(const void *);

#endif  // __COLLECTIONS_TYPES__
