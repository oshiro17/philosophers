#include "philosophers.h"

void	put_initial(t_info *info)
{
	info->fork_num = 0;
	info->eat_num = -1;
	info->die_time = 0;
	info->eat_time = 0;
	info->sleep_time = 0;
}

int	main(int argc, const char *argv[])
{
	t_info	info;

	put_initial(&info);
	if (!check_args(argc, argv, &info))
		return (1);
	
	make_pthread();
	return(0);
}
