# Recipe-and-Nutrition-Program
Brief description:
This program allows the user to work with up to 50 nutrition labels and recipes.
Programmer notes:
This was my final project for a computer sciece class, which heavily uses arrays. I completed the requirements,
however, when the program deletes a label or recipe, I assign the first subscript of the selected recipe array a '#' for comparisons
when searching through arrays to work with. I had to come up with an algorithm to select the proper labels and ingredients. Look at
nutlabels() and reclabels() to see the algorithm. This makes the program run smoothly. All this means that I always have to increment the rows of my arrays, preventing me from reaching 50 labels if I were to delete any of them. If you'd like to check out my program and show me how to fix this problem, I'd appreciate it.

Thanks,
Brendan
