// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        // initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    // Add 1 entry
    add_entries(1);

    // is the collection still empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, size must be 1
    ASSERT_EQ(collection->size(), 1);
}

// Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
    // Add 5 entries
    add_entries(5);
    // is the collection still empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, size must be 5
    ASSERT_EQ(collection->size(), 5);
}

// Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, IsMaxSizeGreaterOrEqualSize)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
    // if empty, the size must be 0
    ASSERT_GE(collection->max_size(), collection->size());

    // add 1 entry
    add_entries(1);
    // is the collection empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, the size must be 1
    ASSERT_EQ(collection->size(), 1);
    // 
    ASSERT_GE(collection->max_size(), collection->size());

    // add 4 entries for a total of 5
    add_entries(4);
    // is the collection empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, the size must be 5
    ASSERT_EQ(collection->size(), 5);
    // check if max size is >= collection size
    ASSERT_GE(collection->max_size(), collection->size());

    // add 5 entries for a total of 10
    add_entries(5);
    // is the collection empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, the size must be 10
    ASSERT_EQ(collection->size(), 10);
    // if empty, the size must be 0
    ASSERT_GE(collection->max_size(), collection->size());
}

// Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, IsCapacityGreaterOrEqualSize)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
    // if empty, the size must be 0
    ASSERT_GE(collection->capacity(), collection->size());

    // add 1 entry
    add_entries(1);
    // is the collection empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, the size must be 1
    ASSERT_EQ(collection->size(), 1);
    // check if collection capacity is >= collection size
    ASSERT_GE(collection->capacity(), collection->size());

    // add 4 entries for a total of 5
    add_entries(4);
    // is the collection empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, the size must be 5
    ASSERT_EQ(collection->size(), 5);
    // check if collection capacity is >= collection size
    ASSERT_GE(collection->capacity(), collection->size());

    // add 5 entries for a total of 10
    add_entries(5);
    // is the collection empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, the size must be 10
    ASSERT_EQ(collection->size(), 10);
    // check if collection capacity is >= collection size
    ASSERT_GE(collection->capacity(), collection->size());
}

// Create a test to verify resizing increases the collection
TEST_F(CollectionTest, CanResizeIncreaseCollection)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
    // resize to 5
    collection->resize(5);
    // is the collection still empty?
    ASSERT_FALSE(collection->empty());
    // if not empty,size must be 5
    ASSERT_EQ(collection->size(), 5);
}

// Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, CanResizeDecreaseCollection)
{
    // add 5 entries
    add_entries(5);
    // is the collection empty?
    ASSERT_FALSE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 5);
    // resize to 1
    collection->resize(1);
    // is the collection still empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, size must be 1
    ASSERT_EQ(collection->size(), 1);
}

// Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, CanResizeDecreaseCollectionToZero)
{
    // add 5 entries
    add_entries(5);
    // is the collection empty?
    ASSERT_FALSE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 5);
    // resize to 1
    collection->resize(0);
    // is the collection still empty?
    ASSERT_TRUE(collection->empty());
    // check if collection has 0 items
    ASSERT_EQ(collection->size(), 0);
}

// Create a test to verify clear erases the collection
TEST_F(CollectionTest, CanClearCollection)
{
    // add 5 entries
    add_entries(5);
    // is the collection empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, size must be 5
    ASSERT_EQ(collection->size(), 5);
    // call the clear function
    collection->clear();
    // check if collection is empty
    ASSERT_TRUE(collection->empty());
    // check if collection size is 0
    ASSERT_EQ(collection->size(), 0);
}

// Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, CanEraseClearCollection)
{
    // add 5 entries
    add_entries(5);
    // is the collection empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, size must be 5
    ASSERT_EQ(collection->size(), 5);
    // call the erase function
    collection->erase(collection->begin(), collection->end());
    // check if collection is empty
    ASSERT_TRUE(collection->empty());
    // check if collection size is 0
    ASSERT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, CanReserveIncreaseCapacity)
{
    // add 5 entries
    add_entries(1);
    // is the collection empty
    ASSERT_FALSE(collection->empty());
    // if not empty, size must be 1
    ASSERT_EQ(collection->size(), 1);
    // what is the capacity?
    ASSERT_EQ(collection->capacity(), 1);
    // call the reserve function
    collection->reserve(6);
    // check the capacity
    ASSERT_EQ(collection->capacity(), 6);
    // check if the size is still 1
    ASSERT_EQ(collection->size(), 1);
}

// Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, CanThrowAtOutOfRange)
{
    // add 5 entries
    add_entries(1);
    // is the collection empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, size must be 1
    ASSERT_EQ(collection->size(), 1);
    // check if the collection at index 2 throws an out or range exception
    ASSERT_THROW(collection->at(2), std::out_of_range);
}

// Custom positive test: Verify that push_back stores the value correctly.
TEST_F(CollectionTest, CanStoreSpecificValue)
{
    // add 42 to end of the collection
    collection->push_back(42);

    // verify size and stored value.
    ASSERT_FALSE(collection->empty());
    ASSERT_EQ(collection->size(), 1);
    ASSERT_EQ(collection->front(), 42);
    ASSERT_EQ(collection->back(), 42);
}

// Custom negative test: Verify reserve throws std::length_error when asked to exceed max_size.
TEST_F(CollectionTest, CanThrowLengthErrorOnReservePastMaxSize)
{
    // ensure the vector throws an error if we try to make it bigger than possible
    ASSERT_THROW(collection->reserve(collection->max_size() + 1), std::length_error);
}