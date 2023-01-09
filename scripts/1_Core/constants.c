/**
 * @brief Since int is implemented here as Int64, I decided to bring everything into it, 
 *        I don’t like these magic symbols that determine the tick frequency,
 *        ask why magic?
 *        because they have this value is constantly different!
 *        It really pisses me off
 *        so on time they can't do it, then I'll do it.
 */
const int TICK_FREQUENCY_MILLIS = 50;

/**
 * @brief Made for those who do not want to count how many ticks per second.
 */
const int TICKS_PER_SECOND = 20;

/**
 * @brief Something like a pointer to call objects on the server or client, or maybe both there and there.
 */
enum DExecuteSide
{
    Server,
    Client,
    Both
}