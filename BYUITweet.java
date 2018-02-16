package brundage;

public class BYUITweet {

    private User user;
    private String text;

    public BYUITweet(User user, String text) {
        this.user = user;
        this.text = text;
    }
    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }
}
