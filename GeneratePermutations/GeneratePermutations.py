def generate(list_of_elements, string):
	if len(list_of_elements) == 0:
		print(string);
	else:
		for num, elem in enumerate(list_of_elements):
			tmp_list = list_of_elements.copy();
			del tmp_list[num];
			generate(tmp_list, string + str(elem))

list_of_elements = [1,2,3,4]

generate(list_of_elements, "");