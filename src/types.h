#ifndef __COLLECTIONS_TYPES__
#define __COLLECTIONS_TYPES__

/**
 * @brief Compare two values and determine which is larger.
 *
 * @return int If the former > the latter, returned value should > 0. If the
 * former == the latter, returned value should == 0. If the former < the latter,
 * returned value should < 0.
 */
typedef int CompareFunction(const void *, const void *);

#endif  // __COLLECTIONS_TYPES__