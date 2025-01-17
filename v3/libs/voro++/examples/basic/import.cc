// Voronoi calculation example code
//
// Author   : Chris H. Rycroft (LBL / UC Berkeley)
// Email    : chr@alum.mit.edu
// Date     : July 1st 2008

#include "voro++.cc"

// Set up constants for the container geometry
const fpoint x_min=-5,x_max=5;
const fpoint y_min=-5,y_max=5;
const fpoint z_min=0,z_max=10;

// Set up the number of blocks that the container is divided
// into.
const int n_x=6,n_y=6,n_z=6;

int main() {
	// Create a container with the geometry given above, and make it
	// non-periodic in each of the three coordinates. Allocate space for
	// eight particles within each computational block
	container con(x_min,x_max,y_min,y_max,z_min,z_max,n_x,n_y,n_z,
			false,false,false,8);

	//Randomly add particles into the container
	con.import("pack_ten_cube");

	// Save the Voronoi network of all the particles to text files
	// in gnuplot and POV-Ray formats
	con.draw_cells_gnuplot("cells_ten_cube.gnu");
	con.draw_cells_pov("cells_ten_cube.pov");

	// Output the particles in POV-Ray format
	con.draw_particles_pov("pack_ten_cube.pov");
}
