while true; do
	battery=$(cat /sys/class/power_supply/BAT1/capacity 2>/dev/null || echo "N/A")
	xsetroot -name " $battery% | $(date '+%a %d %b %H:%M:%S')"
	sleep 1
done
	
