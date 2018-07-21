// Evan Conley & Yiwei Zheng//
package game;

import java.awt.Point;
import java.awt.Rectangle;

public interface Move extends Cloneable
{
	
	int[][] DELTA_XY = { { 4, 0}, { 3, 1}, { 2, 2}, { 1, 3},
            { 0, 4}, {-1, 3}, {-2, 2}, {-3, 1},
            {-4, 0}, {-3,-1}, {-2,-2}, {-1,-3},
            { 0,-4}, { 1,-3}, { 2,-2}, { 3,-1} };

	int[] ANGLES = { 180, 157, 134, 112,
                  90,  67,  44,  22,
                   0, 337, 314, 292,
                 270, 247, 224, 202};
	Point nextposition(Rectangle bounds);
}
