def count_triangles_truly_poly(n):
    """
    Truly polynomial approach using transfer matrices.
    
    Key insight: We can represent the state as (row, min_val, max_val)
    where min_val and max_val represent the range of values that
    can appear in positions of the current row.
    """
    
    # dp[row][min_left][max_right] = number of valid triangles
    # where row 'row' has leftmost value >= min_left and rightmost value <= max_right
    
    from functools import lru_cache
    
    @lru_cache(maxsize=None)
    def dp(row, min_left, max_right):
        if row > n:
            return 1
        
        if min_left > max_right:
            return 0
        
        # Apply diagonal constraint for this row
        actual_max_right = min(max_right, row)
        
        if min_left > actual_max_right:
            return 0
        
        if row == n:
            # Base case: count valid ways to fill bottom row
            return count_monotonic_sequences(n, min_left, actual_max_right)
        
        total = 0
        
        # For each possible leftmost value in current row
        for left_val in range(min_left, actual_max_right + 1):
            # For each possible rightmost value in current row  
            for right_val in range(left_val, actual_max_right + 1):
                # Count ways to fill current row with these boundary values
                current_ways = count_monotonic_sequences(row, left_val, right_val)
                
                # Recursively count remaining rows
                # Next row is constrained: leftmost >= left_val, rightmost <= right_val
                remaining_ways = dp(row + 1, left_val, right_val)
                
                total += current_ways * remaining_ways
        
        return total
    
    @lru_cache(maxsize=None)  
    def count_monotonic_sequences(length, min_val, max_val):
        """Count non-decreasing sequences of given length with values in [min_val, max_val]"""
        if length == 0:
            return 1
        if length == 1:
            return max(0, max_val - min_val + 1)
        if min_val > max_val:
            return 0
        
        # This is stars and bars: we want to count the number of ways to choose
        # length values from range [min_val, max_val] allowing repetition, in non-decreasing order
        # This equals C(max_val - min_val + length, length)
        
        def binomial(n, k):
            if k > n or k < 0:
                return 0
            if k == 0 or k == n:
                return 1
            
            result = 1
            for i in range(min(k, n - k)):
                result = result * (n - i) // (i + 1)
            return result
        
        return binomial(max_val - min_val + length, length)
    
    # Start from row 1 with no initial constraints
    return dp(1, 1, n)


# Test all approaches
if __name__ == "__main__":
    print("Testing all approaches:")
    for i in range(1, 6):
        try:
            result = count_triangles_truly_poly(i)
            print(f"n={i}: {result} triangles")
        except Exception as e:
            print(f"n={i}: Error - {e}")
    
    # Verify n=3 case manually
    print(f"\nManual verification n=3: should be 7")
    print(f"Polynomial approach n=3: {count_triangles_truly_poly(3)}")