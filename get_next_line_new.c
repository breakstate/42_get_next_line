f1 //allocated /reallocate string; (void)?  - - - - needs pos, i, buffer, new - - - -
{
	temp 2 = strsub(pos, BUFF_SIZE - (pos + i));
	temp = strdup(new);
	free(new);
	new = strjoin(temp, temp2)
	free(temp);
	free(temp2);
}

f2 //decision loop;
{
	if (buf[i] != '\n)
		i++;
		return (0);
	else if (buf[i] == \n)
		i++;
		pos = i;
		f1(new and i as size)//----->jump to f1
		return (1);
	else if (r == 0)
	r--;
}

f3 //get_next_line
{
	static, buff, r, pos;
	non static i, new;
	init buffer[buff_size];
	init r = 0;
	f1(allocate buff_size * 1 bytes to new);//no maybe not
	point *line to new;
	
	while (inf)
		if r==0
			if (new)
		   		f1(needs new, buffer)//---> jump to f1 to allocated	
			then read
		while (r > 0)//(maybe remove this while)
			//if f2 return 1, return 1 ----> jump to f2 now, send new and struct
}

/*
 * note:
 * buffer might be declared as buff_size in struct depending on norm else malloc'd
 * */
