double gradient (*pfunc, double x0, double dx)
{
	p = ((*pfunc)(X[x0] + dx) - (*pfunc)(X[x0] - dx))/(2 * dx);
	return p;
}
